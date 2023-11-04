#include<iostream>
#include<string>
#include<fstream>
#include<regex>
#include<cstdlib> 
#include<vector>
#include<map>
using namespace std;

void lexer(string, int);
void display_mainObject(vector<vector<map<string, string>>>);


int main(){
    // Initializing program object (vector of vectors of maps = program that contain lines that contain tokens, where each token is a map of type and image)
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
        lexer(line, lineCount);
    }

    display_mainObject(mainObject); // for testing
    inputFile.close();
    return 0;
}



void lexer(string line, int lineCount, vector<vector<map<string, string>>> mainObject, 
            vector<int> int_value_variables, vector<float> float_value_variables, vector<string> int_name_variables, vector<string> float_name_variables){

    regex EmptyLine("[\\s]*");
    regex CommentLine("[\\s]*#.*[\\s]*");
    regex IntInit("[\\s]*var\\s+int\\s+([a-zA-Z_]+)[\\s]*=[\\s]*([0-9]+)[\\s]*");
    regex FloatInit("[\\s]*var\\s+float\\s+([a-zA-Z_]+)[\\s]*=[\\s]*([0-9]+(\\.([0-9]+)?)?)[\\s]*");
    regex ShowLine("[\\s]*show\\s+(([a-zA-Z_]\\w*|\\d+(\\.\\d+)?|\\.\\d+))[\\s]*");
    regex AddLine("[\\s]*add\\s+([a-zA-Z_]\\w*|\\d+(\\.\\d+)?|\\.\\d+)\\s+to\\s+([a-zA-Z_]\\w*)[\\s]*");
    regex SubstractLine("[\\s]*substract\\s+([a-zA-Z_]\\w*|\\d+(\\.\\d+)?|\\.\\d+)\\s+from\\s+([a-zA-Z_]\\w*)[\\s]*");
    regex DivideLine("[\\s]*divide\\s+([a-zA-Z_]\\w*)\\s+by\\s+([a-zA-Z_]\\w*|\\d+(\\.\\d+)?)[\\s]*");
    regex MultiplyLine("[\\s]*multiply\\s+([a-zA-Z_]\\w*)\\s+with\\s+([a-zA-Z_]\\w*|\\d+(\\.\\d+)?)[\\s]*");
    regex PowerLine("[\\s]*([a-zA-Z_]\\w*|\\d+(\\.\\d+)?)\\s+to\\s+the\\s+power\\s+([a-zA-Z_]\\w*|\\d+(\\.\\d+)?)[\\s]*");
    regex LoopLine("[\\s]*for\\s+([a-zA-Z_]\\w*|_)\\s+to\\s+([a-zA-Z_]\\w*|\\d+)\\s+repeat[\\s]*");
    regex ConditionalLine("[\\s]*if\\s+([a-zA-Z_]\\w*|\\d+(\\.\\d+)?|\\.\\d+)\\s+(>|<|==|!=|>=|<=)\\s+([a-zA-Z_]\\w*|\\d+(\\.\\d+)?|\\.\\d+)\\s+then[\\s]*");
    regex WrongDataType("[\\s]*var\\s+int\\s+([a-zA-Z_]+)[\\s]*=[\\s]*([0-9]+(\\.([0-9]+)?)?)[\\s]*");

    vector<map<string, string>> objectLine;
    smatch parsingArray;
    if(regex_match(line, CommentLine)){

    }else if(regex_match(line, EmptyLine)){


    }else if(regex_match(line, IntInit)){
        // patternNumber = IntInitID;
        if(regex_search(line, parsingArray, IntInit)){

            map<string, string> var;
            var["type"] = "Identifier";
            var["datatype"] = "int";
            var["image"] = parsingArray[1];
            objectLine.push_back(var);

            map<string, string> op;
            op["type"] = "Operator";
            op["image"] = "=";
            objectLine.push_back(op);

            map<string, string> val;
            val["type"] = "Numeric";
            val["image"] = parsingArray[2];
            objectLine.push_back(val);

            mainObject.push_back(objectLine);

        //     for(int i = 0; i < int_name_variables.size(); i++){
        //         if(int_name_variables[i] == parsingArray[1]){
        //             cout << "Initialization Error: You cannot initiate one variable two times (line " << lineCount << ")" << endl;
        //             exit(1);
        //         }
        //     }
        //     for(int i = 0; i < float_name_variables.size(); i++){
        //         if(float_name_variables[i] == parsingArray[1]){
        //             cout << "Initialization Error: You cannot initiate one variable two times (line " << lineCount << ")" << endl;
        //             exit(1);
        //         }
        //     }
        //     int_name_variables.push_back(parsingArray[1]);
        //     int_value_variables.push_back(stoi(parsingArray[2]));
        }


    }else if(regex_match(line, FloatInit)){
        if(regex_search(line, parsingArray, FloatInit)){

            map<string, string> var;
            var["type"] = "Identifier";
            var["datatype"] = "float";
            var["image"] = parsingArray[1];
            objectLine.push_back(var);

            map<string, string> op;
            op["type"] = "Operator";
            op["image"] = "=";
            objectLine.push_back(op);

            map<string, string> val;
            val["type"] = "Numeric";
            val["image"] = parsingArray[2];
            objectLine.push_back(val);

            mainObject.push_back(objectLine);


            // for(int i = 0; i < int_name_variables.size(); i++){
            //     if(int_name_variables[i] == parsingArray[1]){
            //         cout << "Initialization Error: You cannot initiate one variable more than one time (line " << lineCount << ")" << endl;
            //         exit(1);
            //     }
            // }
            // for(int i = 0; i < float_name_variables.size(); i++){
            //     if(float_name_variables[i] == parsingArray[1]){
            //         cout << "Initialization Error: You cannot initiate one variable more than one time (line " << lineCount << ")" << endl;
            //         exit(1);
            //     }
            // }
            // float_name_variables.push_back(parsingArray[1]);
            // float_value_variables.push_back(stoi(parsingArray[2]));
        }


    }else if(regex_match(line, ShowLine)){
        if(regex_search(line, parsingArray, ShowLine)){
            for(int i = 0; i < int_name_variables.size(); i++){
                if(int_name_variables[i] == parsingArray[1]){
                    cout << int_value_variables[i] << endl;
                    return;
                }
            }
            for(int i = 0; i < float_name_variables.size(); i++){
                if(float_name_variables[i] == parsingArray[1]){
                    cout << float_value_variables[i] << endl;
                    return;
                }
            }
            cout << "Initialization Error: Variable " << parsingArray[1] << " is not founded (line " << lineCount << ")" << endl;
            exit(1);
        }


    }else if(regex_match(line, AddLine)){
        if(regex_search(line, parsingArray, AddLine)){
        }
    }else if(regex_match(line, SubstractLine)){
    }else if(regex_match(line, DivideLine)){
    }else if(regex_match(line, MultiplyLine)){
    }else if(regex_match(line, PowerLine)){
    }else if(regex_match(line, LoopLine)){
    }else if(regex_match(line, ConditionalLine)){
    }else if(regex_match(line, WrongDataType)){
        cout << "Initialization Error: Wrong data type (on line number " << lineCount << ")" << endl;
        exit(1);
    }else{
        cout << "Syntax Error (on line number " << lineCount << ")" << endl;
        exit(1);
    }
}


void display_mainObject(vector<vector<map<string, string>>> mainObject){
    for(int i = 0; i < mainObject.size(); i++){
        for(int j = 0; j < mainObject[i].size(); j++){
            cout << mainObject[i][j]["image"] << " ";
        }
        cout << endl;
    }
}
