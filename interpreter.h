#include<vector>
#include<string>
#include<map>
using namespace std;

#ifndef INTERPRETER_H
#define INTERPRETER_H

enum class TokenType;
struct Token;
struct Node;

void interpreter(Node* root, vector<int>& int_values, vector<float>& float_values, vector<string>& int_names, vector<string>& float_names, vector<int>& condition, int& toPass);

#endif