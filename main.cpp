#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"tokenizer.h"
#include"parser.h"
#include"interpreter.h"
using namespace std;

void tokenizer(string line, int lineCount, vector<Token>& lineObject);
Node* makeTree(vector<Token>& lineObject);
void clearTree(Node* root);
void interpreter(Node& root, 
                vector<int>& int_values,
                vector<float>& float_values,
                vector<string>& int_names,
                vector<string>& float_names);




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

void display_mainObject(vector<Token> lineObject){
    for(int i = 0; i < lineObject.size(); i++){
        cout << lineObject[i].value << " ";
    }
    cout << endl;
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
        cout << "Tokenizer passed" << endl;
        display_mainObject(lineObject); 

        Node* root = new Node();
        root = makeTree(lineObject);
        cout << "Parser passed" << endl;

        interpreter(*root, int_values, float_values, int_names, float_names);
        cout << "Interpreter passed" << endl;
        // clearTree(root);
        cout << "Line " << lineCount << " is passed" << endl;
    }

    inputFile.close();
    return 0;
}







