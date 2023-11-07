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
    // LinkedNode is hadled manually
    Init,
    Show,
    OpenParen,
    CloseParen,
};



struct Token {
    TokenType type;
    string value;
};

struct Node {
    Token token;
    Node* leftChild;
    Node* rightChild;
    
    int depth;
};

void clearTree(Node& root);


Node* createNode(Token token){
    Node* newNode = new Node();
    newNode->token = token;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}
void makeNullChildren(Node* node){
    node->leftChild = NULL;
    node->rightChild = NULL;
}

Node* insert(Node* root, Token& token) {
    // If the tree is empty, create a new node and return it
    if (root == nullptr) {
        return createNode(token);
    }

    // If the priority is greater or equal, insert in the right subtree
    if (token.type >= root->token.type) {
        root->leftChild = insert(root->leftChild, token);
    }
    // If the priority is lower, insert in the left subtree
    else {
        root->leftChild = insert(root->leftChild, token);
    }

    // Return the updated root
    return root;
}

void inorderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }
    inorderTraversal(root->leftChild);
    std::cout << root->token.value;
    inorderTraversal(root->rightChild);
}

Node* makeAST(vector<Token>& lineObject){

    Node* root = (Node*)malloc(sizeof(Node));
    for(int i = 0; i < lineObject.size(); i++){
        root = insert(root, lineObject[i]);
    }



    // if(lineObject[0].type == TokenType::Init){
    //     root->token = lineObject[0];

    //     Node* varInit = (Node*)malloc(sizeof(Node));
    //     varInit->token = lineObject[1];
    //    makeNullChildren(varInit);

    //     root->leftChild = varInit;
    //     root->rightChild = NULL;
    //     return root;
    // }else if(lineObject[0].type == TokenType::Show){
    //     root->token = lineObject[0];
    //     Node* varName = (Node*)malloc(sizeof(Node));
    //     varName->token = lineObject[1];
    //     makeNullChildren(varName);

    //     root->leftChild = varName;
    //     root->rightChild = NULL;
    //     return root;
    // }else{
    //     // oh shit, here we go again
    //     // Case of expressions

    //     root->token = lineObject[0];
    //     Node* transversalNode = root;
    //     for(int i = 1; i < lineObject.size(); i++){
    //         while(lineObject[0].type > transversalNode->token.type){
                
    //         }
    //         // here we we swap the nodes when we reach the node that is higher or equal
            
    //     }


    // }  


    return root;
}


