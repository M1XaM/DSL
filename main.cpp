#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"tokenizer.h"
#include"parser.h"
using namespace std;

void inorderTraversal(Node* root);
Node* insert(Node* root, Token& token);



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
};

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
    // display_mainObject(mainObject); // for testing
    inputFile.close();


    vector<int> int_values;
    vector<float> float_values;
    vector<string> int_names;
    vector<string> float_names;
    for(int i = 0; i < mainObject.size(); i++){
        vector<Token> tokens = mainObject[i];
        Node* root = (Node*)malloc(sizeof(Node));
        for(int j = 0; j < tokens.size(); j++){
            root = insert(root, tokens[j]);
        }
        inorderTraversal(root);
        free(root);

        // vector<Token> lineObject = mainObject[i];
        // Node* root = makeAST(lineObject);
        // interpreter(root, int_values, ...);
        // clearTree(root);
    }
    return 0;
}







