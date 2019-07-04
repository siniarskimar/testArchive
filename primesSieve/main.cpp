#include <iostream>
#include <vector>
#include <cmath>

int main(int argc, char** argv) {
    {
        typedef unsigned long calc_t;
        constexpr calc_t max = 100000000;
        bool* primes = new bool[max];

        for(calc_t i = 2; i < max; i++)
            primes[i] = true;

        for(calc_t i = 2; i < sqrt(max); i++) {
            if(primes[i] == true) {
                int k = 1;
                for(calc_t j = pow(i, 2); j < max; j = pow(i, 2) + k * i) {
                    primes[j] = false;
                    k++;
                }
            }
            
        }
        for(calc_t i = 2; i < max; i++)
			if(primes[i] == true)
				std::cout << i << " ";
        std::cout << std::endl;
        delete primes;
    }

    std::cin.get();
    return 0;
}