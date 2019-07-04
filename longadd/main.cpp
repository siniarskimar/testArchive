#include <iostream>
#include <string>
#include <algorithm>

#define ctoi(x) ((x) - '0')
#define itoc(x) ((x) + '0')

std::string longadd(std::string num1, std::string num2) {
    std::string result = "";

    std::reverse(num1.begin(), num1.end());
    std::reverse(num2.begin(), num2.end());

    while(num2.length() < num1.length()) {
        num2 += '0';
    }

    while(num2.length() > num1.length()) {
        num1 += '0';
    }

    int rest = 0;
    for(int i = 0; i < num1.length(); i++) {
        int digit1 = ctoi(num1[i]);
        int digit2 = ctoi(num2[i]);
        std::string sum = std::to_string(digit1 + digit2 + rest);
        if(sum.length() == 2){
            rest = ctoi(sum[0]);
            result += sum[1];
        } else {
            rest = 0;
            result += sum[0];
        }
    }
    
    // If there is a trailing 1 we need add it to result
    if(rest)
        result.insert(result.length()-1, 1, itoc(rest)); // Remember strings are reversed

    std::reverse(result.begin(), result.end());
    return result;
}

int main() {
    std::string num1, num2;
    std::cin >> num1 >> num2;

    std::cout << num1 << "+" << num2 << "=" << longadd(num1, num2) << std::endl;
    return 0;
}