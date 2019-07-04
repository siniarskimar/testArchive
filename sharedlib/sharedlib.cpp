#include <sharedlib.h>

LIBAPI void hello() {
	std::cout << "Hello from sharedlib.dll" << std::endl;
}