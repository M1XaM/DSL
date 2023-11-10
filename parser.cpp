#include<iostream>
#include<vector>
#include<string>
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

void clearTree(Node* root) {
    if (root == nullptr) {
        return;
    }
    clearTree(root->leftChild);
    clearTree(root->rightChild);
    delete root;
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

Node* makeTree(vector<Token>& lineObject){
    if(lineObject[0].type == TokenType::Show){
        Node* root = createNode(lineObject[0]);
        root->rightChild = createNode(lineObject[1]); // we can show just the variables
        return root;

    }else if(lineObject[0].type == TokenType::Init){
        Node* root = createNode(lineObject[0]);
        root->rightChild = nullptr;
        lineObject.erase(lineObject.begin());
        root->leftChild = makeTree(lineObject);
        return root;

    }else{
        Node* root = createNode(lineObject[0]);
        for(int i = 1; i < lineObject.size(); i++){
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
                        Node* tempNode = root;
                        root = workingNode;
                        workingNode->leftChild = tempNode;
                        delete tempNode;
                    }else{
                        previousNode->rightChild = workingNode;
                        workingNode->rightChild = parentNode;
                    }
                    break;
                }
            }   
        }
        return root;
    }
}
