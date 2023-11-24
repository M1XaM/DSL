#ifndef COMMON_H
#define COMMON_H

#include<string>
enum class TokenType{
    Rep = 4, If = 5, Init = 6, Show = 7,
    Equal = 8,
    Plus = 9, Minus = 9,
    Multiply = 10, Divide = 10,
    Power = 11,
    Number = 12, Identifier = 12,
};

struct Token {
    TokenType type;
    std::string value;
};

struct Node {
    TokenType type;
    std::string value;
    Node* left;
    Node* right;
    int priority;
};

#endif
