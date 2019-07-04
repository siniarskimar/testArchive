#include "test.h"
namespace test {
    Application* _app;
    int Start(Application* app, int argc, char** argv){
        _app = app;
        _app->Run();
        return 0;
    }
}