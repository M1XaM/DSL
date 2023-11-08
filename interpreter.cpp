#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<cmath>
using namespace std;

enum class TokenType{
    Equal = 1,
    Plus = 2, Minus = 2,
    Multiply = 3, Divide = 3,
    Power = 4,
    Number = 5, Identifier = 5,
    OpenParen = 6, CloseParen = 6,
    Init, Show,
};

struct Token {
    TokenType type;
    string value;
};

struct Node {
    TokenType type;
    string value;
    Node* leftChild;
    Node* rightChild;
    int priority;
    int depth;
};


bool isOperation(Node& node) {
    if(node.value == "+" || node.value == "-" || node.value == "*" || node.value == "/" || node.value == "**"){
        return true;
    }
    return false;
}

bool haveValues(Node& node){
    if(node.rightChild->type == TokenType::Number || node.rightChild->type == TokenType::Identifier){
        return true;
    }
    return false;

}

Node* performOperation(Node& node, vector<int>& int_values, vector<float>& float_values, vector<string>& int_names, vector<string>& float_names){
    // Make new node that will numeric node, that will replace old operation node
    Node* newNode = new Node();
    newNode->rightChild = nullptr;
    newNode->leftChild = nullptr;

    float leftValue, rightValue, finalValue;
    if(node.leftChild->type == TokenType::Identifier){
        // Find the identifier's value 
    }else{
        leftValue = stof(node.leftChild->value);
    }
    if(node.rightChild->type == TokenType::Identifier){
        // Find the identifier's value 
    }else{
        rightValue = stof(node.rightChild->value);
    }

    if(node.value == "+"){
        finalValue = leftValue + rightValue;
    }else if(node.value == "-"){
        finalValue = leftValue - rightValue;
    }else if(node.value == "*"){
        finalValue = leftValue * rightValue;
    }else if(node.value == "/"){
        finalValue = leftValue / rightValue;
    }else if(node.value == "**"){
        finalValue = pow(leftValue, rightValue);
    }

    newNode->type = TokenType::Number;
    newNode->priority = static_cast<int>(newNode->type);
    newNode->value = to_string(finalValue);
    return newNode;
}

// Postorder travers (LRN)
void interpreter(Node& root, vector<int>& int_values, vector<float>& float_values, vector<string>& int_names, vector<string>& float_names){
    if(&root == nullptr){
        return;
    }

    // Handle Show, Initialization and Assigment
    if(root.type == TokenType::Show){
        for(int i = 0; i < int_names.size(); i++){
            if(int_names[i] == root.rightChild->value){
                cout << int_values[i] << endl;
                return;
            }
        }
    }else if(root.type == TokenType::Init){
        if(root.value == "int"){
            int_names.push_back(root.leftChild->leftChild->value);
            int_values.push_back(stoi(root.leftChild->rightChild->value));
        }else if(root.value == "float"){
            float_names.push_back(root.leftChild->leftChild->value);
            float_values.push_back(stof(root.leftChild->rightChild->value));
        }
    }
    

    interpreter(*root.leftChild, int_values, float_values, int_names, float_names);
    interpreter(*root.rightChild, int_values, float_values, int_names, float_names);

    // Perform operation if case
    if(isOperation(root) && haveValues(root)){
        root = *(performOperation(root, int_values, float_values, int_names, float_names));
    }

    
}
