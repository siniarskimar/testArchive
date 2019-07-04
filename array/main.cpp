#include <iostream>
#include <exception>
template<typename _Type, unsigned int _SizeMax>
class Array {
    _Type* m_arr;

public:
    Array() {
        m_arr = new _Type[_SizeMax];
    }
    ~Array(){
        delete m_arr;
    }
    unsigned int size() const { return _SizeMax; }

    _Type& get(unsigned int index) {
        if(index > size())
            throw std::range_error("Index out of range");
        return m_arr[index];
    }

    _Type& operator[](int x){
        return get(x);
    }
};

int main(int argc, char** argv) {
    {
        Array<Array<int,5>, 1> arr;
        arr[0][0] = 10;
        std::cout << arr[0][0] << std::endl;
    }
    std::cin.get();
    return 0;
}