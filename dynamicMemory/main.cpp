#include <iostream>
#include <vector>
#include <limits>
class DynamicMemory {
public:
    struct DynamicElement {
        void* elem = nullptr;
        void* end = nullptr;
        size_t size;
    };
    DynamicMemory(size_t bytes) {
        m_memory = new char[bytes];
        m_end = m_memory + bytes;
        m_elements.reserve(10);
    }
    ~DynamicMemory() {
        delete m_memory;
    }

    template<typename T, typename... Args>
    T* allocate(Args... args) {
        size_t size = sizeof(T);
        if(m_elements.size() == 0) {
            DynamicElement elem;
            create<T>(elem, m_memory, size, args...);
            m_elements.push_back(elem);
            return (T*) elem.elem;
        }
        for(int i = 0; i < m_elements.size(); i++) {
            DynamicElement& elem = m_elements[i];
            if(m_elements.size() == i + 1 && elem.end == m_end || ((char*)(elem.end) - (char*)(m_end)) < size) {
                return nullptr; // No available memory
            }

            // If there is only one element or did not found free memory in-between elements and there is memory left
            if(m_elements.size() == 1 || (m_elements.size() == i + 1 && elem.end != m_end)) {
                DynamicElement next;
                create<T>(next, elem.end, size, args...);
                m_elements.push_back(next);
                return (T*) next.elem;
            }
            DynamicElement& next = m_elements[i + 1];
            int spaceLeft = ((char*) (next.elem) - (char*) (elem.end));
            if(size <= spaceLeft) { // if there is enough space in beetween elements
                DynamicElement n;
                create<T>(n, elem.end, size, args...);
                m_elements.insert(m_elements.begin() + i + 1, n);
                return (T*) n.elem;
            }
        }
    }

    void deallocate(void* ptr) {
        for(int i = 0; i < m_elements.size(); i++) {
            DynamicElement& elem = m_elements[i];
            if(elem.elem == ptr) {
                m_elements.erase(m_elements.begin() + i); // No need fo delete, left memory will be overriden
                break;
            }
        }
    }

private:
	template<typename T,typename... Args>
	void create(DynamicElement& elem, void* location,size_t size, Args... args) {
        elem.elem = new(location) T(args...);
		elem.size = size;
        elem.end = (char*) elem.elem + elem.size;
	}
    char* m_memory;
    void* m_end;

    std::vector<DynamicElement> m_elements;
};

int main(int argc, char** argv) {
    {
        DynamicMemory mem(sizeof(int)*2);

        int* i = mem.allocate<int>(std::numeric_limits<int>::max());
        int* k = mem.allocate<int>(std::numeric_limits<int>::max());
        int* m = mem.allocate<int>(std::numeric_limits<int>::min());

        mem.deallocate(i);
        mem.deallocate(m);
        mem.deallocate(k);
    }

    std::cin.get();
    return 0;
}