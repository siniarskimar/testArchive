#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <exception>

class String {
    char* m_str = nullptr;
    size_t m_length;

public:
    //Constructors
    String()
        : String("") {}

    String(const char* str) {
        std::cout << "String constructed" << std::endl;
        resize(strlen(str));
        strcpy(m_str, str);
    }

    ~String() {
        delete[] m_str;
    }

    String(String& prevObj) {
        m_length = prevObj.length();
        resize(length());
        strcpy(m_str, prevObj.str());
    }

public:
    // Methods
    void concat(const String& other) {
        resize(length() + other.length());
        strcat(m_str, other.str());
    }
    void concat(const char* other) {
        size_t size = length() + strlen(other) + 1;

        char* catRes = new char[size];
        memset(catRes, 0, sizeof(char) * size);

        strcat(strcat(catRes, str()), other);
        catRes[size] = '\0';

        if(m_str != nullptr)
            delete[] m_str;
        m_str = catRes;
    }
    void concat(char other) {
        size_t size = length() + 1 + 1;

        char* catRes = new char[size];
        memset(catRes, 0, sizeof(char) * size);

        strcat(catRes, str());
        catRes[size - 2] = other;
        catRes[size - 1] = '\0';

        if(m_str != nullptr)
            delete[] m_str;
        m_str = catRes;
    }

    static String concat(const String& left, const String& right) {
        size_t length = left.length() + right.length();

        char* catRes = new char[length];
        memset(catRes, 0, sizeof(char) * length);

        strcat(strcat(catRes, left.str()), right.str());

        return catRes;
    }

    static String concat(const String& left, const char* right) {
        size_t length = left.length() + strlen(right);

        char* catRes = new char[length];
        memset(catRes, 0, sizeof(char) * length);

        strcat(strcat(catRes, left.str()), right);

        return catRes;
    }
    static String concat(const String& left, char other) {
        size_t size = left.length() + 1 + 1;

        char* catRes = new char[size];
        memset(catRes, 0, sizeof(char) * size);

        strcat(catRes, left.str());
        catRes[size - 2] = other;
        catRes[size - 1] = '\0';

        return catRes;
    }

private:
    void resize(size_t size) {
        if(m_str != nullptr)
            delete[] m_str;

        setLength(size);
        size_t tmp_length = length();

        m_str = new char[tmp_length + 1];
        memset(m_str, 0, sizeof(char) * tmp_length + 1);

        m_str[tmp_length] = '\0';
    }

public:
    // Overloads
    String& operator=(const String& other) {
        setLength(other.length());
        resize(length());
        strcpy(m_str, other.str());
        return *this;
    }

    String& operator=(const char* str) {
        setLength(strlen(str));
        resize(length());
        strcpy(Str(), str);
        return *this;
    }

    String operator+(const String& other) {
        return concat(*this, other);
    }

    String operator+(const char* other) {
        return concat(*this, other);
    }
    String operator+(char ch) {
        return concat(*this, ch);
    }

    String& operator+=(char ch) {
        this->concat(ch);
        return *this;
    }

    char& operator[](size_t index) {
        if(index > length() || index < 0)
            throw std::runtime_error("Ouf of bounds");
        return (Str()[index]);
    }

    const char& operator[](size_t index) const {
        if(index > length() || index < 0)
            throw std::runtime_error("Ouf of bounds");
        return (str()[index]);
    }

    friend std::ostream& operator<<(std::ostream& stream, String& str) {
        stream << str.m_str;
        return stream;
    }

public:
    // Geters and Setters
    size_t length() const { return m_length; }
    const char* str() const { return Str(); } // implicit conversion from char* to const char*

private:
    void setLength(size_t lenght) { m_length = lenght; }
    char* Str() const { return m_str; }
};

int main(int argc, char** argv) {
    {
        String str = "Hell";
        String str2 = str + 'o';
        //(((str += 'H') += 'e') += 'l') += 'l';
        std::cout << str2 << std::endl;
    }

    std::cin.get();
    return 0;
}