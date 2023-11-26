#include<iostream>
#include<string>
#include<fstream>
#include<vector>

#include"components/tokenizer.h"
#include"components/parser.h"
#include"components/interpreter.h"
#include"components/structs.h"
using namespace std;

void tokenizer(string line, int lineCount, vector<Token>& lineObject);
Node* parser(vector<Token>& lineObject);
void interpreter(Node* root, vector<int>& condition);


int main(){
    // string filename;
    // cout << "Enter the name of exisiting file: ";
    // cin >> filename;
    // ifstream inputFile(filename);
    ifstream inputFile("inputTests/loop.faf"); 
    if (!inputFile.is_open()){
        cout << "Error opening the file." << endl;
        return 1;
    }

    static vector<int> condition = {1};

    string line;
    int lineCount = 0;
    while(getline(inputFile, line)){
        lineCount += 1;
        
        vector<Token> lineObject;
        tokenizer(line, lineCount, lineObject);
        if(lineObject.size() == 0) continue;
    
        Node* root = new Node();
        root = parser(lineObject);

        interpreter(root, condition);
    }

    inputFile.close();
    if(condition.size() > 1){
        cout << "Syntax Error: There is an if statement that is not 'closed' (unpredictable behavior may occur)" << endl;
        exit(1);
    }

    return 0;
}







