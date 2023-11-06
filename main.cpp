#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib> 
#include<vector>
#include<typeinfo>
#include<cctype>
#include<stdexcept>
#include<functional>
#include"tokenizer.h"
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
    std::string value;
    std::vector<ASTNode*> children;
};

struct Parser {
    std::vector<Token> tokens;
    size_t currentTokenIndex;

    Token getCurrentToken() {
        if (currentTokenIndex < tokens.size()) {
            return tokens[currentTokenIndex];
        }
        return Token{TokenType::Identifier, ""};  // Return a dummy token for the end of input
    }

    void consumeToken() {
        ++currentTokenIndex;
    }
};

ASTNode* parseFactor(Parser&);

ASTNode* createBinaryOperationNode(const std::string& op, ASTNode* left, ASTNode* right) {
    ASTNode* node = new ASTNode{op, {left, right}};
    return node;
}
ASTNode* createTerminalNode(const std::string& value) {
    ASTNode* node = new ASTNode{value, {}};
    return node;
}

ASTNode* parseExpression(Parser& parser);

ASTNode* parseTerm(Parser& parser) {
    ASTNode* node = parseFactor(parser);
    while (parser.getCurrentToken().type == TokenType::Multiply || parser.getCurrentToken().type == TokenType::Divide) {
        Token op = parser.getCurrentToken();
        parser.consumeToken();
        ASTNode* right = parseFactor(parser);
        node = createBinaryOperationNode(op.value, node, right);
    }
    return node;
}

ASTNode* parseFactor(Parser& parser) {
    Token currentToken = parser.getCurrentToken();
    if (currentToken.type == TokenType::Number || currentToken.type == TokenType::Identifier) {
        parser.consumeToken();
        return createTerminalNode(currentToken.value);
    } else if (currentToken.type == TokenType::OpenParen) {
        parser.consumeToken();
        ASTNode* node = parseExpression(parser);
        if (parser.getCurrentToken().type == TokenType::CloseParen) {
            parser.consumeToken();
            return node;
        } else {
            throw std::runtime_error("Expected closing parenthesis");
        }
    } else {
        throw std::runtime_error("Unexpected token");
    }
}

ASTNode* parseExpression(Parser& parser) {
    ASTNode* node = parseTerm(parser);
    while (parser.getCurrentToken().type == TokenType::Plus || parser.getCurrentToken().type == TokenType::Minus) {
        Token op = parser.getCurrentToken();
        parser.consumeToken();
        ASTNode* right = parseTerm(parser);
        node = createBinaryOperationNode(op.value, node, right);
    }
    return node;
}

void printOpeningParenthesis(){
    std::cout << "(";
}
void printClosingParenthesis(){
    std::cout << ")";
}
void printNodeValue(const ASTNode* node){
    std::cout << node->value;
}

// Function to perform in-order traversal and print AST elements
void printAST(const ASTNode* node) {
    if (node) {
        if (!node->children.empty()) {
            printOpeningParenthesis();
        }

        for (size_t i = 0; i < node->children.size(); ++i) {
            printAST(node->children[i]);

            if (i < node->children.size() - 1) {
                std::cout << " " << node->value << " ";
            }
        }

        if (!node->children.empty()) {
            printClosingParenthesis();
        } else {
            printNodeValue(node);
        }
    }
}


void display_mainObject(vector<vector<Token>> mainObject){
    for(int i = 0; i < mainObject.size(); i++){
        for(int j = 0; j < mainObject[i].size(); j++){
            cout << mainObject[i][j].value << " ";
        }
        cout << endl;
    }
}
int main(){
    vector<vector<Token>> mainObject;

    // string filename;
    // cout << "Enter the name of exisiting file: ";
    // cin >> filename;
    // ifstream inputFile(filename);
    ifstream inputFile("file.faf"); // for testing

    if (!inputFile.is_open()){
        cout << "Error opening the file." << endl;
        return 1;
    }


    string line;
    int lineCount = 0;
    while(getline(inputFile, line)){
        lineCount += 1;
        tokenizer(line, lineCount, mainObject);
    }
    display_mainObject(mainObject); // for testing
    inputFile.close();



    // for(int i = 0; i < mainObject.size(); i++){
    //     Parser parser{mainObject[i], 0};
    //     ASTNode* root = parseExpression(parser);
    //     // printAST(&root);
    // }
    // return 0;
}







