#include <iostream>
#include <iomanip>

struct MemoryBlock {
    void* memory = nullptr;
    size_t size;
    bool free = false;
    MemoryBlock* prev = nullptr;
    MemoryBlock* next = nullptr;
};

class MemoryAllocator {
public:
    MemoryAllocator() = default;

    virtual ~MemoryAllocator() {
        MemoryBlock* mem = m_start;
        MemoryBlock* next;
        while(mem != nullptr) {
            next = mem->next;

            if(!mem->free) {

                delete[]((char*) (mem->memory));
            }

            delete mem;
        }
    }

    template<typename T>
    T* allocate(size_t count = 1) {
        size_t size = sizeof(T) * count;

        MemoryBlock* mem = m_start;

        if(m_start) {

            while(mem != nullptr) {
                if(mem->free && mem->size == size) {
                    break;
                }
                mem = mem->next;
            }

            if(mem != nullptr) {
                mem->free = false;
            } else {

                m_end->next = new MemoryBlock();
                mem = m_end->next;
                mem->prev = m_end;

                mem->size = size;
                mem->memory = new char[mem->size];
                m_end = mem;
            }

        } else {
            mem = new MemoryBlock();
            mem->size = size;
            mem->memory = new char[mem->size];

            m_start = mem;
            m_end = m_start;
        }

        memset(mem->memory, 0, mem->size);

        return ((T*) mem->memory);
    }

    template<typename T, typename... Arg>
    void construct(T* ptr, Arg... arg) {
        if(!m_start)
            return;

        MemoryBlock* it = getBlock(ptr);

        if(it == nullptr)
            return;

        new((char*) it->memory) T(arg...);
    }

    
    void deallocate(void* ptr);
    void shrink();
    void destroy(void* ptr);

private:
    MemoryBlock* getBlock(void* ptr);
    void destroy(MemoryBlock* mem);

private:
    MemoryBlock* m_start = nullptr;
    MemoryBlock* m_end = nullptr;
};

int main(int argc, char** argv) {
    {
        MemoryAllocator memAlloc;

    }
    std::cin.get();
    return 0;
}

MemoryBlock* MemoryAllocator::getBlock(void* ptr) {
    MemoryBlock* it = m_start;
    while(it != nullptr) {
        if(it->memory == ptr)
            break;
        it = it->next;
    }
    return it;
}

void MemoryAllocator::shrink() {
    MemoryBlock* it = m_start;
    MemoryBlock* next;
    MemoryBlock* prev;
    while(it != nullptr) {
        next = it->next;
        prev = it->prev;

        if(it->free) {
            if(next) {
                next->prev = prev;
            }
            if(prev) {
                prev->next = next;
            }

            delete[]((char*) it->memory); // Memory was allocated as char* (array) before

            if(it == m_start && it == m_end) { // There was only one element
                m_start = nullptr;
                m_end = nullptr;
            }

            delete it;
        }

        it = next;
    }
}

void MemoryAllocator::destroy(void* ptr) {
    if(!m_start)
        return;
    destroy(getBlock(ptr));
}

void MemoryAllocator::destroy(MemoryBlock* ptr) {
    if(!m_start || ptr == nullptr)
        return;

	memset(ptr->memory, 0, ptr->size);
    ptr->free = true;
}

void MemoryAllocator::deallocate(void* ptr) {
    if(!m_start)
        return;

    MemoryBlock* it = getBlock(ptr);

    if(it == nullptr)
        return;

    if(it->prev) {
        it->prev->next = it->next;
        if(it == m_end)
            m_end = it->prev;
    }
    if(it->next) {
        it->next->prev = it->prev;
        if(it == m_start)
            m_start = it->next;
    }

    if(it == m_start && it == m_end) {
        m_start = nullptr;
        m_end = nullptr;
    }

    if(!it->free)
        destroy(it);

    delete it;
}