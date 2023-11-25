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
void clearTree(Node* root);
void interpreter(Node* root, 
                
                vector<int>& condition,
                int& toPass);




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
    ifstream inputFile("inputTests/loop.faf"); 
    if (!inputFile.is_open()){
        cout << "Error opening the file." << endl;
        return 1;
    }

    

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

        interpreter(root, condition, toPass);
        // clearTree(root);
        // the tree will be deleted in interpreter (in future), because of loop conditions

        
    }
    inputFile.close();

    if(condition.size() > 1){
        cout << "Syntax Error: There is an if statement that is not 'closed' (unpredictable behavior may occur)" << endl;
        exit(1);
    }


    return 0;
}







