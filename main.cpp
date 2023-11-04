#include<iostream>
#include<string>
#include<fstream>
#include<regex>
#include<cstdlib> 
#include<vector>
#include<map>
#include"lexer.h"
using namespace std;

void lexer(string, int, vector<vector<map<string, string>>>&);
void display_mainObject(vector<vector<map<string, string>>>);


int main(){
    // Initializing program object (vector of vectors of maps = program that contain lines that contain tokens, where each token is a map of type, image, and may contain some others fields)
    vector<vector<map<string, string>>> mainObject;
    vector<int> int_value_variables;
    vector<float> float_value_variables;
    vector<string> int_name_variables;
    vector<string> float_name_variables;

    // string filename;
    // cout << "Enter the name of exisiting file: ";
    // cin >> filename;
    // ifstream inputFile(filename);
    ifstream inputFile("file.faf"); // for testing

    if (!inputFile.is_open()){
        cout << "Error opening the file." << endl;
        return 1;
    }

    // Lexer makes mainObject (json-like object)
    string line;
    int lineCount = 0;
    while(getline(inputFile, line)){
        lineCount += 1;
        lexer(line, lineCount, mainObject);
    }

    display_mainObject(mainObject); // for testing
    inputFile.close();
    return 0;
}


void display_mainObject(vector<vector<map<string, string>>> mainObject){
    for(int i = 0; i < mainObject.size(); i++){
        for(int j = 0; j < mainObject[i].size(); j++){
            cout << mainObject[i][j]["image"] << " ";
        }
        cout << endl;
    }
}


