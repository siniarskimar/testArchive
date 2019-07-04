#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <array>
#include <string>
#include <algorithm>
#include <chrono>
template<typename T, int arrSize>
void gnomeSort(std::array<T, arrSize>& arr) {
    if(arrSize <= 1)
        return;
    int i = 1;
    do {
        if(arr[i] >= arr[i - 1]) {
            i++;
            continue;
        }
        if(arr[i] < arr[i - 1]) {
            std::swap(arr[i], arr[i - 1]);
            i--;
        }
    } while(i != (arrSize - 1));
}
template<typename T, int arrSize>
void gnomeSort(std::array<std::string, arrSize>& arr) {
    static_assert(true, "Can not sort strings");
}

template<typename T, int arrSize>
int quickSortPart(std::array<T, arrSize>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for(int j = low; j <= high - 1; j++) {
        if(arr[j] <= pivot) {
            i++; // increment index of smaller element
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}
template<typename T, int arrSize>
void quickSort(std::array<T, arrSize>& arr, int low, int high) {
    if(low < high) {
        int i = quickSortPart(arr, low, high);
        quickSort(arr, low, i - 1);
        quickSort(arr, i, high);
    }
}
void swap(int* left, int* right) {
    int temp = *left;
    *left = *right;
    *right = temp;
}

void selectionSort(int* arr, int arrSize) {
    int minI = 0;
    for(int i = 0; i < arrSize - 1; i++) {
        minI = i;
        for(int j = i; j < arrSize; j++) {
            if(arr[j] < arr[minI])
                minI = j;
        }
        std::cout << std::endl;
        swap(&arr[minI], &arr[i]);
    }
}

int main(int argc, char** argv) {
    {
        std::setprecision(10);
        constexpr int size = 100;
        std::array<int, size> arr;
        for(int i = 0; i < size; i++) {
            arr[i] = i;
        }
        std::random_shuffle(arr.begin(), arr.end());
        auto start = std::chrono::high_resolution_clock::now();
        /*std::cout << "Before:" << std::endl;
        for(int i = 0; i < 5; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;*/

        gnomeSort(arr);
        //quickSort(arr, 0, 5 - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::cout << duration.count() << " miliseconds" << std::endl;
        //selectionSort(arr.data(), arr.size());

        /*std::cout << "After:" << std::endl;
        for(int i = 0; i < 5; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;*/
    }

    std::cin.get();
    return 0;
}