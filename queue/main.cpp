#include <iostream>
template<typename T>
class Queue {
    struct Element {
        Element* prev = nullptr;
        T data;
    };
    Element* m_front;
    Element* m_back;

public:
    Queue()
        : m_front(nullptr), m_back(nullptr) {}
    ~Queue() {
        Element* tmp = m_front;
        while(tmp) {
            Element* prev = tmp->prev;
            delete tmp;
            tmp = prev;
        }
    }
    void push(T data) {
        Element* elem = new Element;
        elem->data = data;

        if(m_back)
            m_back->prev = elem;
        if(!m_front)
            m_front = elem;
        m_back = elem;
    }
    void pop() {
        if(!m_front)
            return;
        Element* prev = m_front->prev;

        delete m_front;
        m_front = prev;
    }
    T front() {
        if(m_front)
            return m_front->data;
        else
            return 0;
    }
};
int main(int argc, char** argv) {

    {
        Queue<int> queue;
        queue.push(1);
        queue.push(2);
        queue.push(3);
        queue.push(4);

        for(int i = 0; i < 4; i++) {
            std::cout << queue.front() << std::endl;
            queue.pop();
        }
    }

    std::cin.get();
    return 0;
}