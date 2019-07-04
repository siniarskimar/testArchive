#include <iostream>
#include "test.h"

class App : public test::Application {
public:
    void Run() {
        std::cout << "Hello World" << std::endl;
        std::cin.get();
    }
};

int main(int argc, char** argv) {
    int rtn = 0;
    App* app = new App();
    rtn = test::Start(app, argc, argv);
    return rtn;
}