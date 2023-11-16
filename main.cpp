#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"tokenizer.h"
#include"parser.h"
#include"interpreter.h"
using namespace std;

void tokenizer(string line, int lineCount, vector<Token>& lineObject);
Node* parser(vector<Token>& lineObject);
void clearTree(Node* root);
void interpreter(Node* root, 
                vector<int>& int_values,
                vector<float>& float_values,
                vector<string>& int_names,
                vector<string>& float_names);


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

void travers(Node* root){
    if(root != nullptr){
        cout << root->value << " ";
        travers(root->left);
        travers(root->right);
        
    }
}


int main(){
    // string filename;
    // cout << "Enter the name of exisiting file: ";
    // cin >> filename;
    // ifstream inputFile(filename);
    ifstream inputFile("file.faf"); 
    if (!inputFile.is_open()){
        cout << "Error opening the file." << endl;
        return 1;
    }

    // For interpreter
    static vector<int> int_values;
    static vector<float> float_values;
    static vector<string> int_names;
    static vector<string> float_names;

    string line;
    int lineCount = 0;
    while(getline(inputFile, line)){
        lineCount += 1;
        
        vector<Token> lineObject;
        tokenizer(line, lineCount, lineObject);
        if(lineObject.size() == 0) continue;

        // for(int i = 0; i < lineObject.size(); i++){
        //     cout << " <" << lineObject[i].value << "> ";
        // }
        // cout << '\n';
        
    
        
        Node* root = new Node();
        root = parser(lineObject);
        // travers(root);
        // printBinaryTree(root);
        // cout << '\n';

        interpreter(root, int_values, float_values, int_names, float_names);
        clearTree(root);
    }
    inputFile.close();
    return 0;
}







