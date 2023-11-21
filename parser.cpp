#include<iostream>
#include<vector>
#include<string>
using namespace std;

enum class TokenType{
    Rep = 4, If = 5, Init = 6, Show = 7,    Equal = 8,
    Plus = 9, Minus = 9,
    Multiply = 10, Divide = 10,
    Power = 11,
    Number = 12, Identifier = 12,
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

void clearTree(Node* root){
    // cout << root->value << endl;
    if(root->left == nullptr && root->right == nullptr){
        delete root;
        return;
    }
    if(root->left != nullptr){
        clearTree(root->left);
    }
    if(root->right != nullptr){
        clearTree(root->right);
    }
}

Node* createNode(Token token){
    Node* newNode = new Node();
    newNode->type = token.type;
    newNode->value = token.value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->priority = static_cast<int>(token.type);
    return newNode;
}

Node* mathExpression(vector<Token>& lineObject){
    Node* root = createNode(lineObject[0]);
    lineObject.erase(lineObject.begin());
    for(int i = 0; i < lineObject.size(); i++){
        Node* workingNode = createNode(lineObject[i]);
        Node* parentNode = root;
        Node* previousNode = nullptr;
        while(true){
            if(workingNode->priority > parentNode->priority){
                if(parentNode->left == nullptr){
                    parentNode->left = workingNode;
                    break;
                }else if(parentNode->right == nullptr){
                    parentNode->right = workingNode;
                    break;
                }else{
                    previousNode = parentNode;
                    parentNode = parentNode->right;
                }
            }else if(workingNode->priority <= parentNode->priority){
                if(previousNode == nullptr){ // we are on root node
                    workingNode->left = root;
                    root = workingNode;
                    break;
                }else{
                    previousNode->right = workingNode;
                    workingNode->left = parentNode;
                    break;
                }
            }   
        }
    }
    return root;
}

Node* parser(vector<Token>& lineObject){
    Node* root = createNode(lineObject[0]);
    if(root->type == TokenType::Show){
        lineObject.erase(lineObject.begin());
        root->left = mathExpression(lineObject);
    }else if(root->type == TokenType::Init){
        lineObject.erase(lineObject.begin());
        root->left = mathExpression(lineObject);
    }else if(root->type == TokenType::If && root->value == "if"){
        root->left = createNode(lineObject[2]); // if already exists, this is equal
        root->left->left = createNode(lineObject[1]); // this is varname
        lineObject.erase(lineObject.begin()); // erasing if
        lineObject.erase(lineObject.begin()); // erasing varname
        lineObject.erase(lineObject.begin()); // erasing equal
        root->left->right = mathExpression(lineObject); // evaluating the expression after the equal sign
    }else if(root->type == TokenType::If && root->value == "endif"){
        // If it's endif statement - the root is already formed
    }else if(root->type == TokenType::Rep && root->value == "repeat"){
        lineObject.erase(lineObject.begin());
        root->left = mathExpression(lineObject);
    }else if(root->type == TokenType::Rep && root->value == "endrepeat"){
        // If it's endrepeat statement - the root is already formed
    }else{
        root = mathExpression(lineObject);
        // cout << root->value << " " << int(root->type) << endl;
        // cout << root->left->value << " " << int(root->left->type) << endl;
        // cout << root->left->left->value << " " << int(root->left->left->type) << endl;
        // cout << root->left->left->left->value << " " << int(root->left->left->left->type) << endl;
        // cout << root->left->left->right->value << " " << int(root->left->left->left->left->type) << endl;
        // cout << endl;

        // cout << root->left->right->value << endl;
        // cout << root->left->right->right->value << endl;

        // cout << root->right->value << endl;
        // cout << root->right->left->value << endl;
        // cout << root->right->right->value << " " << root->right->right->priority << endl;
    }

    return root;
}
