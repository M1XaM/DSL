#include<vector>
#include<string>
#include<map>
using namespace std;

#ifndef PARSER_H
#define PARSER_H

enum class TokenType;
struct Token;
struct ASTNode;

ASTNode* makeAST(vector<Token>& lineObject);
void clearTree(ASTNode& root);

#endif 
