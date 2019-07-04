#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>

namespace ptr {
    template<typename T>
    class Controller {
        struct Data {
            uint32_t count = 0;
            T* data = nullptr;

            ~Data() {
                if(data)
                    delete data;
            }
        };
        Data* data = nullptr;

    public:
        Controller() {
            if(!data)
                data = new Data();
            (*data).count++;
        }

        Controller(const Controller& prev) {
            data = prev.data;
            (*data).count++;
        }

        ~Controller() {
            (*data).count--;
            if(data->count <= 0)
                delete data;
        }
        Data* getData() const { return data; }
    };

    template<typename T>
    class SharedPointer {
        Controller<T> m_controller;

    public:
        SharedPointer() {}
        virtual ~SharedPointer() {}
        SharedPointer& operator=(T* var) {
            m_controller.getData()->data = var;
            return *this;
        }
        T* get() const {
            return m_controller.getData()->data;
        }
    };
} // namespace ptr

int main(int argc, char** argv) {
	{
		ptr::SharedPointer<int> sptr;
		{
			auto sptr2 = sptr;
			sptr2 = new int(5);
		}
		{
			std::cout << *(sptr.get()) << std::endl;
		}
	}
    std::cin.get();
    return 0;
}