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
    int depth;
};

Node* createNode(Token token){
    Node* newNode = new Node();
    newNode->type = token.type;
    newNode->value = token.value;
    newNode->leftChild = nullptr;
    newNode->rightChild = nullptr;
    newNode->priority = static_cast<int>(token.type);
    return newNode;
}
void makeNullChildren(Node* node){
    node->leftChild = nullptr;
    node->rightChild = nullptr;
}

Node* makeTree(vector<Token>& lineObject){
    Node* root = new Node();
    root = createNode(lineObject[0]);
    makeNullChildren(root);

    // Handling Show, Init
    if(root->type == TokenType::Show){
        root->rightChild = new Node();
        root->rightChild->type == TokenType::Identifier;  // we can show just the variables
        root->rightChild->value == lineObject[1].value;
        return root;
    }else if(root->type == TokenType::Init){
        root->rightChild = nullptr;

        root->leftChild = createNode(lineObject[2]);
        root->leftChild->leftChild = createNode(lineObject[1]);
        lineObject.erase(lineObject.begin());
        lineObject.erase(lineObject.begin());
        lineObject.erase(lineObject.begin()); 
        root->leftChild->rightChild = makeTree(lineObject);

    }

    // Handling math expressions
    for(int i = 1; i < lineObject.size(); i++){
        // here we start to put tokens in tree, starting from second
        Node* workingNode = createNode(lineObject[i]);
        Node* parentNode = root;

        // The node goes down to the leaves
        while(true){
            if(workingNode->priority > parentNode->priority){
                if(parentNode->rightChild == nullptr){
                    parentNode->rightChild = workingNode;
                    break;
                }else{
                    parentNode = parentNode->rightChild;
                }
            }else if(workingNode->priority < parentNode->priority){
                if(parentNode->leftChild == nullptr){
                    parentNode->leftChild = workingNode;
                    break;
                }else{
                    parentNode = parentNode->leftChild;
                }
            }else{

                // Priority is equal, insert the new node in place of the current node
                workingNode->leftChild = parentNode->leftChild;
                workingNode->rightChild = parentNode->rightChild;
                parentNode->rightChild = nullptr;
                parentNode->leftChild = workingNode;
                break;
            }
        }

    }
    return root;
}
