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
                vector<string>& float_names,
                vector<int>& condition,
                int& toPass);


enum class TokenType{
    If = 5, Init = 6, Show = 7,
    Equal = 8,
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
    ifstream inputFile("inputTests/test.faf"); 
    if (!inputFile.is_open()){
        cout << "Error opening the file." << endl;
        return 1;
    }

    // For interpreter
    static vector<int> int_values;
    static vector<float> float_values;
    static vector<string> int_names;
    static vector<string> float_names;
    static vector<int> condition = {1};
    static int toPass = 0;  // how many endif statements should be passed
    // This can happen when an if statement is under no execution state, so his endif statement should not affect condition vector

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

        interpreter(root, int_values, float_values, int_names, float_names, condition, toPass);
        clearTree(root);
    }
    inputFile.close();

    if(condition.size() > 1){
        cout << "Syntax Error: There is an if statement that is not 'closed' (unpredictable behavior may occur)" << endl;
        exit(1);
    }


    return 0;
}







