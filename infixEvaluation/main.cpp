#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <stack>
#include <queue>
#include <map>
#include <cctype>

static std::map<char, uint8_t> predecence;

class Token {
public:
    enum class TokenType {
        Unknown = -1,
        Digit = 1,
        Operator,
        LeftParen,
        RightParen
    };

    Token(std::string token, int pred = -1, TokenType type = TokenType::Unknown, bool rightAssoc = false)
        : m_type(type), m_token(token), m_rightAssoc(rightAssoc), m_precedence(pred) {}

    bool IsRightAssociative() const { return m_rightAssoc; }
    void IsRightAssociative(bool rightAssoc) { m_rightAssoc = rightAssoc; }
    void IsRightAssociative(bool& rightAssoc) { m_rightAssoc = rightAssoc; }

    void Set(std::string token) { m_token = token; }
    void Set(std::string& token) { m_token = token; }
    void SetPrecedence(int prece) { m_precedence = prece; }
    void SetPrecedence(int& prece) { m_precedence = prece; }

    std::string Get() const { return m_token; }
    TokenType GetType() const { return m_type; }
    int GetPredecence() const { return m_precedence; }

private:
    TokenType m_type{TokenType::Unknown};
    std::string m_token{};
    bool m_rightAssoc{false};
    int m_precedence{-1};
};

double eval(double l, double r, char operat) {
    double res = 0;
    switch(operat) {
    case '+':
        res = l + r;
        break;
    case '-':
        res = l - r;
        break;
    case '*':
        res = l * r;
        break;
    case '/':
        res = l / r;
        break;
    default:
        break;
    }
    return res;
}

std::string infixToPostfix(std::string infix) {
    std::stack<char> operatorStack;
    std::string postfix = "";
    /*for(char c : infix) {
        if(c == ' ')
            continue;

        if(std::isdigit(c)) {
            postfix += c;
        } else if(c == '(') {
            operatorStack.push(c);
        } else if(c == ')') {
            while(!operatorStack.empty() && (operatorStack.top() != '(')) {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            if(!operatorStack.empty()) {
                if(operatorStack.top() == '(')
                    operatorStack.pop();
            }
        } else if(predecence.find(c) != predecence.end()) {
            while(!operatorStack.empty() && ((predecence[operatorStack.top()] >= predecence[c]) && (operatorStack.top() != '('))) {
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(c);
        }
    }
    while(!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }*/
    return postfix;
}

//double evalueatePostfix(std::string postfix) {
//}

int main(int argc, char** argv) {
    {

        std::string infix = "3 + 4 * (4 - 1)";
        double result = 0;
        predecence['-'] = 1;
        predecence['+'] = 1;
        predecence['*'] = 2;
        predecence['/'] = 2;
        std::cout << infixToPostfix(infix) << std::endl;
    }
    std::cin.get();
    return 0;
}
