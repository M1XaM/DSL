#ifndef INTERPRETER_H
#define INTERPRETER_H

#include<iostream>
#include<vector>
#include<string>
#include"structs.h"
using namespace std;
static vector<LoopNode*> LoopList;
static int activeLoop = -1;

bool isOperation(Node* node) {
    return (node->value == "+" || node->value == "-" || node->value == "*" || node->value == "/");
}

bool haveValues(Node* node){
    return (node->left->type == TokenType::Number || node->left->type == TokenType::Identifier) &&
           (node->right->type == TokenType::Number || node->right->type == TokenType::Identifier);
}


void performOperation(Node* node, vector<int>& int_values, vector<float>& float_values, vector<string>& int_names, vector<string>& float_names){
    float leftValue, rightValue, finalValue;


    if(isalpha((node->left->value)[0])){
        for(int i = 0; i < int_names.size(); i++){
            if(int_names[i] == node->left->value){
                leftValue = int_values[i];
            }
        }
        for(int i = 0; i < float_names.size(); i++){
            if(float_names[i] == node->left->value){
                leftValue = float_values[i];
            }
        }
    }else{
        leftValue = stof(node->left->value);
    }

    if(isalpha((node->right->value)[0])){
        for(int i = 0; i < int_names.size(); i++){
            if(int_names[i] == node->right->value){
                rightValue = int_values[i];
            }
        }
        for(int i = 0; i < float_names.size(); i++){
            if(float_names[i] == node->right->value){
                rightValue = float_values[i];
            }
        }        
    }else{
        rightValue = stof(node->right->value);
    }

    if(node->value == "+"){
        finalValue = leftValue + rightValue;
    }else if(node->value == "-"){
        finalValue = leftValue - rightValue;
    }else if(node->value == "*"){
        finalValue = leftValue * rightValue;
    }else if(node->value == "/"){
        if(rightValue == 0){
            cout << "Division Error: You cannot divide by zero" << endl;
            exit(1);
        }
        finalValue = leftValue / rightValue;
    }

    node->right = nullptr;
    node->left = nullptr;
    node->type = TokenType::Number;
    node->priority = static_cast<int>(node->type);
    node->value = to_string(finalValue);
}

void recursiveMathExpression(Node* root, vector<int>& int_values, vector<float>& float_values, vector<string>& int_names, vector<string>& float_names){
    if (root->left == nullptr && root->right == nullptr) return;
    recursiveMathExpression(root->left, int_values, float_values, int_names, float_names);
    recursiveMathExpression(root->right, int_values, float_values, int_names, float_names);

    if(isOperation(root) && haveValues(root)){
        // Transform Operation Node to a Number Node
        // cout << "operation start" << endl;
        performOperation(root, int_values, float_values, int_names, float_names);
        return;
    }
}

LoopNode* makeLoopNode(Node* root){
    LoopNode* loopNode = new LoopNode;
    loopNode->n = stoi(root->left->value);
    loopNode->initial_n = stoi(root->left->value);

    return loopNode;
}

void interpreter(Node* root, vector<int>& int_values, vector<float>& float_values, vector<string>& int_names, vector<string>& float_names, vector<int>& condition, int& toPass);

void iterateLoopNode(LoopNode* loopNode, vector<int>& int_values, vector<float>& float_values, vector<string>& int_names, vector<string>& float_names, vector<int>& condition, int& toPass){
    for(int i = 0; i < loopNode->initial_n; i++){
        for(int i = 0; i < loopNode->roots.size(); i++){
            if(loopNode->roots.at(i)->isItLoop == 0){
                interpreter(loopNode->actualRoot, int_values, float_values, int_names, float_names, condition, toPass);
            }else{
                iterateLoopNode(loopNode->roots.at(i), int_values, float_values, int_names, float_names, condition, toPass);
            }
        }
    }
}

void interpreter(Node* root, vector<int>& int_values, vector<float>& float_values, vector<string>& int_names, vector<string>& float_names, vector<int>& condition, int& toPass){
    // Implementing "passing" endif statements (this block of code must be in the beggining)
    if(root->value == "endif"){
        if(condition.back() == 0 && toPass > 0){
            toPass -= 1;
            return;
        }
        if(condition.size() > 1){
            condition.pop_back();
            return;
        }else{
            cout << "Syntax Error: To many endif statements" << endl;
            exit(1);
        }
    }
    if(condition.back() == 0 && root->value == "if"){
        toPass += 1;
        return;
    }else if(condition.back() == 0){
        return;
    }
    


    // Make loop node
    if(root->value == "repeat"){
        if(LoopList.size() == 0){ // first loop is the most basic
            LoopNode* loopStat = makeLoopNode(root);
            LoopList.push_back(loopStat);
        }else{  // if exist outter loop, add it to its roots
            LoopNode* loopStat = makeLoopNode(root);
            loopStat->isItLoop = 1;
            LoopList.back()->roots.push_back(loopStat);
            LoopList.push_back(loopStat);
        }
        activeLoop += 1;
        return;
    }else if(root->value == "endrepeat"){
        activeLoop -= 1;
        if(activeLoop == -1 && LoopList.size() > 0){  // check if we start iterating
            int iterations  = LoopList.at(0)->initial_n;
            // Recursion starts directly from first LoopNode
            iterateLoopNode(LoopList.at(0), int_values, float_values, int_names, float_names, condition, toPass);
            LoopList.clear();
        }
        return;
    }

    // Add statements in active loop
    // LoopNode have roots that are just another LoopNode, so we have to make our root into LoopNode but to interpret it like a simple root
    if(activeLoop > -1){
        LoopNode* notLoop = new LoopNode;
        notLoop->isItLoop = 0;
        notLoop->actualRoot = root;
        // LoopList.at(activeLoop)->roots.push_back(notLoop);
        return;
    }
    

    


    




    

    if(root->type == TokenType::Show){
        // cout << "showing var" << endl;
        if(isOperation(root->left)){
            recursiveMathExpression(root->left, int_values, float_values, int_names, float_names);
            cout << root->left->value << endl;
            return;
        }else if(isalpha((root->left->value)[0])){
            for(int i = 0; i < int_names.size(); i++){
                if(int_names[i] == root->left->value){
                    cout << int_values[i] << endl;
                    return;
                }
            }
            for(int i = 0; i < float_names.size(); i++){
                if(float_names[i] == root->left->value){
                    cout << float_values[i] << endl;
                    return;
                }
            }
            cout << "Initialization Error: Variable " <<  root->left->value << " was not initiated." << endl;
            exit(1);
        }else{
            cout << root->left->value << endl;
            return;
        }


    }else if(root->type == TokenType::Init){  // Create new variable with a value
        // cout << "creating new var" << endl;
        Node* varNode = root->left->left;
        recursiveMathExpression(root->left->right, int_values, float_values, int_names, float_names);
        Node* numNode =  root->left->right;

        for(int i = 0; i < int_names.size(); i++){
            if(int_names[i] == varNode->value){
                cout << "Initialization Error: Cannot initiate one variable two times" << endl;
                exit(1);
            }
        }
        for(int i = 0; i < float_names.size(); i++){
            if(float_names[i] == varNode->value){
                cout << "Initialization Error: Cannot initiate one variable two times" << endl;
                exit(1);
            }
        }
        if(root->value == "int"){
            int_names.push_back(varNode->value);
            int_values.push_back(stoi(numNode->value));
        }else if(root->value == "float"){
            float_names.push_back(varNode->value);
            float_values.push_back(stof(numNode->value));
        }
        return;

    }else if(root->type == TokenType::If){  // Evaluating if-statement
        float firstPart, secondPart;
        // Second Part of if-statement (after the equal)
        if(isOperation(root->left->right)){  
            recursiveMathExpression(root->left->right, int_values, float_values, int_names, float_names);
            secondPart = stof(root->left->right->value);
        }else if(isalpha((root->left->right->value)[0])){
            for(int i = 0; i < int_names.size(); i++){
                if(int_names[i] == root->left->right->value){
                    secondPart = int_values[i];
                }
            }
            for(int j = 0; j < float_names.size(); j++){
                if(float_names[j] == root->left->right->value){
                    secondPart = float_values[j];
                }
            }
        }else{
            secondPart = stof(root->left->right->value);
        }

        // First Part of if-statement (before the equal)
        for(int i = 0; i < int_names.size(); i++){
            if(int_names[i] == root->left->left->value){
                firstPart = int_values[i];
            }
        }
        for(int j = 0; j < float_names.size(); j++){
            if(float_names[j] == root->left->left->value){
                firstPart = float_values[j];
            }
        }
        
        // Evaluating the truthness of expression
        if(firstPart == secondPart){
            condition.push_back(1);
        }else{
            condition.push_back(0);
        }
        // cout << "pass" << endl;
        return;

    // Assign a value to existent variable
    }else if(root->type == TokenType::Equal && root->left->type == TokenType::Identifier ){ // && root->right->type == TokenType::Number
        // cout << "assigment start" << endl;
        recursiveMathExpression(root->right, int_values, float_values, int_names, float_names);
        float toAssignValue;
        if(isalpha((root->right->value)[0])){
            for(int i = 0; i < int_names.size(); i++){
                if(int_names[i] == root->right->value){
                    toAssignValue = int_values[i];
                }
            }
            for(int j = 0; j < float_names.size(); j++){
                if(float_names[j] == root->right->value){
                    toAssignValue = float_values[j];
                }
            }
        }else{
            toAssignValue = stof(root->right->value);
        }

        for(int i = 0; i < int_names.size(); i++){
            if(int_names[i] == root->left->value){
                int_values[i] = static_cast<int>(toAssignValue);
                return;
            }
        }
        for(int i = 0; i < float_names.size(); i++){
            if(float_names[i] == root->left->value){
                float_values[i] = toAssignValue;
                return;
            }
        }
        cout << "Initialization Error: Variable was not initiated" << endl;
        exit(1);

    }
}

#endif