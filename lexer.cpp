#include<iostream>
#include<string>
#include<fstream>
#include<regex>
#include<cstdlib> 
using namespace std;

enum Pattern {
    EmptyLineID = 1,
    CommentLineID,
    IntInitID,
    FloatInitID,
    ShowLineID,
    AddLineID,
    SubstractLineID,
    DivideLineID,
    MultiplyLineID,
    PowerLineID,
    LoopLineID,
    ConditionalLineID
};

int main(){

    return 0;
}

int lexer(string line, int lineCount, vector<vector<map<string, string>>> mainObject){
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

    // ofstream outputFile("file.inter.faf");
    // if (!outputFile.is_open()) {
    //     cout << "Error opening the file." << endl;
    //     return 1;
    // }

    vector<map<string, string>> objectLine;
    smatch parsingArray;
    Pattern patternNumber;
    if(regex_match(line, CommentLine)){
        patternNumber = CommentLineID;
    }else if(regex_match(line, EmptyLine)){
        patternNumber = EmptyLineID;


    }else if(regex_match(line, IntInit)){
        // patternNumber = IntInitID;
        if(regex_search(line, parsingArray, IntInit)){
            map<string, string> intInitiate;
            intInitiate["type"] = "DataType";
            intInitiate["image"] = "int";
            objectLine.push_back(intInitiate);

            map<string, string> var;
            var["type"] = "Identifier";
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
        patternNumber = FloatInitID;
        if(regex_search(line, parsingArray, FloatInit)){

            map<string, string> intInitiate;
            intInitiate["type"] = "DataType";
            intInitiate["image"] = "float";
            objectLine.push_back(intInitiate);

            map<string, string> var;
            var["type"] = "Identifier";
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
        patternNumber = ShowLineID;
        if(regex_search(line, parsingArray, ShowLine)){
            for(int i = 0; i < int_name_variables.size(); i++){
                if(int_name_variables[i] == parsingArray[1]){
                    cout << int_value_variables[i] << endl;
                    return patternNumber;
                }
            }
            for(int i = 0; i < float_name_variables.size(); i++){
                if(float_name_variables[i] == parsingArray[1]){
                    cout << float_value_variables[i] << endl;
                    return patternNumber;
                }
            }
            cout << "Initialization Error: Variable " << parsingArray[1] << " is not founded (line " << lineCount << ")" << endl;
            exit(1);
        }


    }else if(regex_match(line, AddLine)){
        patternNumber = AddLineID;
        if(regex_search(line, parsingArray, AddLine)){
        }
    }else if(regex_match(line, SubstractLine)){
        patternNumber = SubstractLineID;
    }else if(regex_match(line, DivideLine)){
        patternNumber = DivideLineID;
    }else if(regex_match(line, MultiplyLine)){
        patternNumber = MultiplyLineID;
    }else if(regex_match(line, PowerLine)){
        patternNumber = PowerLineID;
    }else if(regex_match(line, LoopLine)){
        patternNumber = LoopLineID;
    }else if(regex_match(line, ConditionalLine)){
        patternNumber = ConditionalLineID;
    }else{
        cout << "Syntax Error (on line number " << lineCount << ")" << endl;
        exit(1);
    }
    
    return patternNumber;
}