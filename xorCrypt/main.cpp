#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>

// std::string xorCrypt(std::string str, char key){
//     if(str.length() == 0)
//         return str;
//     for(int i = 0; i < str.size(); i++){
//         str[i] ^= key;
//     }
//     return str;
// }

void escapeChars(std::string& str){
    static char chars[8] = {'\a','\n','\t','\r','\v','\b','\e','\f'};
    for(int i = 0; i < str.length() - 1; i++) {
        for(int j = 0; j < 8; j++){
            if(str[i] == chars[j]){
                str.insert(str.end() - (8 - i), '\\');
            }
        }
    }
}

std::string xorCrypt(std::string str, std::string key){
    for(int i = 0; i < str.length() - 1; i++)
        str[i] ^= key[i%key.size()];
    return str;
}

int main(int argc, char** argv) {
    {
        if(argc <= 1){
            std::cout << "Missing argument: string" << std::endl;
            return 1;
        }
        std::string str(argv[1], strlen(argv[1]));

        std::string enc = xorCrypt(str, "hello");
        std::string enc_copy = enc;
        escapeChars(enc_copy);
        std::cout << enc_copy << std::endl;

        std::cout << xorCrypt(enc, "hello") << std::endl;
    }

    std::cin.get();
    return 0;
}