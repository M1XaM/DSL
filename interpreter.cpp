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
};

bool isOperation(Node& node) {
    return (node.value == "+" || node.value == "-" || node.value == "*" || node.value == "/" || node.value == "**");
}

bool haveValues(Node& node){
    return (node.rightChild->type == TokenType::Number || node.rightChild->type == TokenType::Identifier);
}


Node* performOperation(Node& node, vector<int>& int_values, vector<float>& float_values, vector<string>& int_names, vector<string>& float_names){
    // Make new numeric node, that will replace old operation node
    Node* newNode = new Node();
    newNode->rightChild = nullptr;
    newNode->leftChild = nullptr;

    // Handle variable in math expression
    float leftValue, rightValue, finalValue;
    if(node.leftChild->type == TokenType::Identifier){
        for(int i = 0; i < int_names.size(); i++){
            if(int_names[i] == node.leftChild->value){
                leftValue = int_values[i];
            }
        }
        for(int i = 0; i < float_names.size(); i++){
            if(float_names[i] == node.leftChild->value){
                leftValue = float_values[i];
            }
        }
    }else{
        leftValue = stof(node.leftChild->value);
    }
    if(node.rightChild->type == TokenType::Identifier){
        // Find the identifier's value 
        for(int i = 0; i < int_names.size(); i++){
            if(int_names[i] == node.leftChild->value){
                leftValue = int_values[i];
            }
        }
        for(int i = 0; i < float_names.size(); i++){
            if(float_names[i] == node.leftChild->value){
                leftValue = float_values[i];
            }
        }        
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

void interpreter(Node& root, vector<int>& int_values, vector<float>& float_values, vector<string>& int_names, vector<string>& float_names){
    cout << "interpreter start" << endl;

    if(isOperation(root) && haveValues(root)){
        cout << "operation start" << endl;
        root = *(performOperation(root, int_values, float_values, int_names, float_names));

    }else if(root.type == TokenType::Equal && root.leftChild->type == TokenType::Identifier && root.rightChild->type == TokenType::Number){
        // Assign a value to existent variable
        cout << "assigment statement start" << endl;
        for(int i = 0; i < int_names.size(); i++){
            if(int_names[i] == root.leftChild->value){
                int_values[i] = static_cast<int>((stof(root.rightChild->value)));
                return;
            }
        }
        for(int i = 0; i < float_names.size(); i++){
            if(float_names[i] == root.leftChild->value){
                float_values[i] = stof(root.rightChild->value);
                return;
            }
        }
        cout << "Initialization Error: Variable was not initiate" << endl;
        exit(1);

    }else if(root.type == TokenType::Init){
        cout << "creating new var" << endl;
        // Create new variable with a value
        Node* varNode = root.leftChild->leftChild;
        Node* numNode = root.leftChild->rightChild;

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
        if(root.value == "int"){
            int_names.push_back(varNode->value);
            int_values.push_back(stoi(numNode->value));
        }else if(root.value == "float"){
            float_names.push_back(varNode->value);
            float_values.push_back(stof(numNode->value));
        }

        cout << int_names[0] << endl;
    }else if(root.type == TokenType::Show){
        cout << "showing var start" << endl;
        // Show existent VARIABLE
        cout << root.leftChild->value << endl;
    }else if(root.type == TokenType::Number){
        cout << "return start" << endl;
        return;
    }else{
        cout << "recursive start" << endl;
        interpreter(*(root.leftChild), int_values, float_values, int_names, float_names);
        cout << "the right one is choosed" << endl;
        interpreter(*(root.rightChild), int_values, float_values, int_names, float_names);
    }
}
