#include <iostream>

template<typename T>
class Stack {
	struct Element {
		T data;
		Element* prev = nullptr;
	};
	Element* top = nullptr;
	int m_size = 0;

public:

    ~Stack(){
        while(!isEmpty()){
            pop();
        }
    }
	void push(T data) {
		Element* tmp = new Element;
		tmp->data = data;

		if(top) {
			tmp->prev = top;
		}
		top = tmp;
		m_size++;
	}
	T pop() {
		Element* tmp = top;
		Element* back = top->prev;

		if(!tmp)
			return 0;

		top = back;

		T data = tmp->data;
		delete tmp;

		m_size--;
		return data;
	}
	int size() const {return m_size;}
	bool isEmpty() { return top == nullptr; }
};


int main(int argc, char** argv){
	Stack<int> stack;

	if(stack.isEmpty())
		std::cout << "Empty" << std::endl;

	stack.push(1);
	stack.push(2);
	stack.push(3);
	stack.push(4);

    if(stack.isEmpty())
		std::cout << "Empty" << std::endl;


	std::cout << stack.pop() << std::endl;
	std::cout << stack.pop() << std::endl;
	std::cout << stack.pop() << std::endl;
	std::cout << stack.pop() << std::endl;

	std::cin.get();
	return 0;
}