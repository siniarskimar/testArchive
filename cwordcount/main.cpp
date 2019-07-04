#include <iostream>

size_t wordCount(const char* word, unsigned int progress) {

    //Dla czytelności
    const char* curr = word + progress;
    const char* next = word + progress + 1;
                                                             // Moja logika po angielsku
    if(((*curr) >= 33 && (*curr) <= 126) && (*next) == '\0') // If current char is A-z and next char is null byte (end)
        return 1;                                            // Count it as word
    else if((*curr) == ' ' && (*next) == '\0')               // If current char is space and next char is null byte (end)
        return 0;                                            // Dont count spaces before null byte (end)
    else if((*curr) != ' ' && (*next) == ' ')                // If current char is not space  and next char is space
        return 1 + wordCount(word, progress + 1);            // Count 1 word and process next char
    else                                                     // If in the middle of the word or multiple spaces occured
        return wordCount(word, progress + 1);                // Process further
}

//Default
size_t wordCount(const char* word) {
    return wordCount(word, 0);
}

int main(int argc, char** argv) {
    std::cout << wordCount("Marysia ma kota  !") << std::endl;
    std::cin.get();
    return 0;
}