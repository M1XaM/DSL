#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"tokenizer.h"
#include"parser.h"
#include"interpreter.h"
using namespace std;

Node* makeTree(vector<Token>& lineObject);
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
    int depth;
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
    ifstream inputFile("file.faf"); 

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


    // For interpreter
    static vector<int> int_values;
    static vector<float> float_values;
    static vector<string> int_names;
    static vector<string> float_names;

    for(int i = 0; i < mainObject.size(); i++){

        // Send to parser
        Node* root = new Node();
        root = makeTree(mainObject[i]);

        // Send to interpreter
        interpreter(*root, int_values, float_values, int_names, float_names);
    }
    
    return 0;
}







