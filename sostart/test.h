#ifndef __TEST_H_
#define __TEST_H_

#ifdef _WIN32
#ifdef TEST_BUILD_DLL
#define TEST_API __declspec(dllexport)
#else
#define TEST_API __declspec(dllimport)
#endif
#endif

namespace test {
    class TEST_API Application {
    public:
        virtual void Run() = 0;
    };
    TEST_API int Start(Application* app, int argc, char** argv);
} // namespace test

#endif