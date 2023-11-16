#include<iostream>
#include<vector>
#include<string>
using namespace std;

enum class TokenType{
    Init = 1, Show = 2,
    Equal = 3,
    Plus = 4, Minus = 4,
    Multiply = 5, Divide = 5,
    Power = 6,
    Number = 7, Identifier = 7,
    OpenParen = 8, CloseParen = 8,
};

struct Token {
    TokenType type;
    string value;
};

struct Node {
    TokenType type;
    string value;
    Node* left;
    Node* right;
    int priority;
};

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

void interpreter(Node* root, vector<int>& int_values, vector<float>& float_values, vector<string>& int_names, vector<string>& float_names){

    if(root->type == TokenType::Show){
        // cout << "showing var" << endl;
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
        cout << "Initiation Error: Variable " <<  root->left->value << " was not initiated." << endl;
        exit(1);
    }else if(root->type == TokenType::Init){
        // cout << "creating new var" << endl;
        // Create new variable with a value
        Node* varNode = root->left->left;
        Node* numNode = root->left->right;

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
    }


    if (root->left == nullptr && root->right == nullptr) return;
    interpreter(root->left, int_values, float_values, int_names, float_names);
    interpreter(root->right, int_values, float_values, int_names, float_names);



    
    if(isOperation(root) && haveValues(root)){
        // Transform Operation Node to a Number Node
        // cout << "operation start" << endl;
        performOperation(root, int_values, float_values, int_names, float_names);
        return;
    }else if(root->type == TokenType::Equal && root->left->type == TokenType::Identifier && root->right->type == TokenType::Number){
        // Assign a value to existent variable
        // cout << "assigment start" << endl;
        for(int i = 0; i < int_names.size(); i++){
            if(int_names[i] == root->left->value){
                int_values[i] = static_cast<int>((stof(root->right->value)));
                return;
            }
        }
        for(int i = 0; i < float_names.size(); i++){
            if(float_names[i] == root->left->value){
                float_values[i] = stof(root->right->value);
                return;
            }
        }
        cout << "Initialization Error: Variable was not initiate" << endl;
        exit(1);

    }
}
