#include<vector>
#include<string>
#include<map>
using namespace std;

#ifndef TOKENIZER_H
#define TOKENIZER_H

enum class TokenType;
struct Token;
void tokenizer(string, int, vector<vector<Token>>&);

#endif 
