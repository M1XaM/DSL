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
    Node* leftChild;
    Node* rightChild;
    int priority;
};

void clearTree(Node* root){
    // cout << root->value << endl;
    if(root->leftChild == nullptr && root->rightChild == nullptr){
        delete root;
        return;
    }
    if(root->leftChild != nullptr){
        clearTree(root->leftChild);
    }
    if(root->rightChild != nullptr){
        clearTree(root->rightChild);
    }
}

Node* createNode(Token token){
    Node* newNode = new Node();
    newNode->type = token.type;
    newNode->value = token.value;
    newNode->leftChild = nullptr;
    newNode->rightChild = nullptr;
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
                if(parentNode->leftChild == nullptr){
                    parentNode->leftChild = workingNode;
                    break;
                }else if(parentNode->rightChild == nullptr){
                    parentNode->rightChild = workingNode;
                    break;
                }else{
                    previousNode = parentNode;
                    parentNode = parentNode->rightChild;
                }
            }else if(workingNode->priority <= parentNode->priority){
                if(previousNode == nullptr){ // we are on root node
                    workingNode->leftChild = root;
                    root = workingNode;
                    break;
                }else{
                    previousNode->rightChild = workingNode;
                    workingNode->leftChild = parentNode;
                    break;
                }
            }   
        }
    }
    return root;
}

Node* makeTree(vector<Token>& lineObject){
    Node* root = createNode(lineObject[0]);
    if(root->type == TokenType::Show){
        root->leftChild = createNode(lineObject[1]);
    }else if(root->type == TokenType::Init){
        lineObject.erase(lineObject.begin());
        root->leftChild = mathExpression(lineObject);
    }else{
        root = mathExpression(lineObject);
        // cout << root->value << " " << int(root->type) << endl;
        // cout << root->leftChild->value << " " << int(root->leftChild->type) << endl;
        // cout << root->leftChild->leftChild->value << " " << int(root->leftChild->leftChild->type) << endl;
        // cout << root->leftChild->leftChild->leftChild->value << " " << int(root->leftChild->leftChild->leftChild->type) << endl;
        // cout << root->leftChild->leftChild->rightChild->value << " " << int(root->leftChild->leftChild->leftChild->leftChild->type) << endl;
        // cout << endl;

        // cout << root->leftChild->rightChild->value << endl;
        // cout << root->leftChild->rightChild->rightChild->value << endl;

        // cout << root->rightChild->value << endl;
        // cout << root->rightChild->leftChild->value << endl;
        // cout << root->rightChild->rightChild->value << endl;
    }

    return root;
}
