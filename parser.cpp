#include<iostream>
#include<vector>
using namespace std;

enum class TokenType{
    Number,
    Identifier,
    Init,
    Show,
    BinaryOperator,
    Plus, 
    Minus,
    Multiply,
    Divide,
    Equal,
    OpenParen,
    CloseParen,
};

struct Token {
    TokenType type;
    string value;
};




struct ASTNode {
    Token token;
    ASTNode* leftChild;
    ASTNode* rightChild;
};

void clearTree(ASTNode& root);
void makeNullChildren(ASTNode* node){
    node->leftChild = NULL;
    node->rightChild = NULL;
}
ASTNode* makeAST(vector<Token>& lineObject){

    ASTNode* root = (ASTNode*)malloc(sizeof(ASTNode));
    for(int i = 0; i < lineObject.size(); i++){
        if(lineObject[i].type == TokenType::Init){
            root->token = lineObject[i];

            ASTNode* varInit = (ASTNode*)malloc(sizeof(ASTNode));
            varInit->token = lineObject[i+1];
            makeNullChildren(varInit);

            root->leftChild = varInit;
            root->rightChild = NULL;
            return root;
        }else if(lineObject[i].type == TokenType::Show){
            root->token = lineObject[i];
            ASTNode* varName = (ASTNode*)malloc(sizeof(ASTNode));
            varName->token = lineObject[i+1];
            makeNullChildren(varName);

            root->leftChild = varName;
            root->rightChild = NULL;
            return root;
        }else{
            // oh shit, here we go again


        }



    }


    return root;
}

