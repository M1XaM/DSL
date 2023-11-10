#include<vector>
#include<string>
#include<map>
using namespace std;

#ifndef PARSER_H
#define PARSER_H

enum class TokenType;
struct Token;
struct Node;

Node* makeTree(vector<Token>& lineObject);
void clearTree(Node* root);

#endif 
