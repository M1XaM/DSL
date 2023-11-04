#include<iostream>
#include<string>
#include<regex>
#include<vector>
#include"lexer.h"
using namespace std;

void lexer(string line, int lineCount, vector<vector<map<string, string>>>& mainObject){

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
        if(regex_search(line, parsingArray, IntInit)){

            map<string, string> intvar;
            intvar["type"] = "Identifier";
            intvar["datatype"] = "int";
            intvar["image"] = parsingArray[1];
            objectLine.push_back(intvar);

            map<string, string> op;
            op["type"] = "Operator";
            op["image"] = "=";
            objectLine.push_back(op);

            map<string, string> intval;
            intval["type"] = "Numeric";
            intval["image"] = parsingArray[2];
            objectLine.push_back(intval);

            mainObject.push_back(objectLine);
        }

    }else if(regex_match(line, FloatInit)){
        if(regex_search(line, parsingArray, FloatInit)){

            map<string, string> floatvar;
            floatvar["type"] = "Identifier";
            floatvar["datatype"] = "float";
            floatvar["image"] = parsingArray[1];
            objectLine.push_back(floatvar);

            map<string, string> op;
            op["type"] = "Operator";
            op["image"] = "=";
            objectLine.push_back(op);

            map<string, string> floatval;
            floatval["type"] = "Numeric";
            floatval["image"] = parsingArray[2];
            objectLine.push_back(floatval);

            mainObject.push_back(objectLine);
        }

    }else if(regex_match(line, ShowLine)){
        if(regex_search(line, parsingArray, ShowLine)){

            map<string, string> showop;
            showop["type"] = "Operator";
            showop["image"] = "show";
            objectLine.push_back(showop);

            map<string, string> var;
            var["type"] = "Identifier";
            var["image"] = parsingArray[1];
            objectLine.push_back(var);

            mainObject.push_back(objectLine);
        }

    }else if(regex_match(line, AddLine)){
        if(regex_search(line, parsingArray, AddLine)){
            map<string, string> var;
            var["type"] = "Identifier";
            var["image"] = parsingArray[3]; // a pair of () are in excess in regex, but for now its working
            objectLine.push_back(var);

            map<string, string> op;
            op["type"] = "Operator";
            op["image"] = "=";
            objectLine.push_back(op);

            map<string, string> samevar;
            samevar["type"] = "Identifier";
            samevar["image"] = parsingArray[3];
            objectLine.push_back(samevar);

            map<string, string> plus;
            plus["type"] = "Operator";
            plus["image"] = "+";
            objectLine.push_back(plus);

            map<string, string> val;
            val["type"] = "Operator";
            val["image"] = parsingArray[1];
            objectLine.push_back(val);

            mainObject.push_back(objectLine);
        }
    }else if(regex_match(line, SubstractLine)){
        if(regex_search(line, parsingArray, SubstractLine)){
            map<string, string> var;
            var["type"] = "Identifier";
            var["image"] = parsingArray[3];
            objectLine.push_back(var);

            map<string, string> op;
            op["type"] = "Operator";
            op["image"] = "=";
            objectLine.push_back(op);

            map<string, string> samevar;
            samevar["type"] = "Identifier";
            samevar["image"] = parsingArray[3];
            objectLine.push_back(samevar);

            map<string, string> minus;
            minus["type"] = "Operator";
            minus["image"] = "-";
            objectLine.push_back(minus);

            map<string, string> val;
            val["type"] = "Operator";
            val["image"] = parsingArray[1];
            objectLine.push_back(val);

            mainObject.push_back(objectLine);
        }        
    }else if(regex_match(line, DivideLine)){
        if(regex_search(line, parsingArray, DivideLine)){
            map<string, string> var;
            var["type"] = "Identifier";
            var["image"] = parsingArray[1];
            objectLine.push_back(var);

            map<string, string> op;
            op["type"] = "Operator";
            op["image"] = "=";
            objectLine.push_back(op);

            map<string, string> samevar;
            samevar["type"] = "Identifier";
            samevar["image"] = parsingArray[1];
            objectLine.push_back(samevar);

            map<string, string> divide;
            divide["type"] = "Operator";
            divide["image"] = ":";
            objectLine.push_back(divide);

            map<string, string> val;
            val["type"] = "Operator";
            val["image"] = parsingArray[2];
            objectLine.push_back(val);

            mainObject.push_back(objectLine);
        }                
    }else if(regex_match(line, MultiplyLine)){
        if(regex_search(line, parsingArray, MultiplyLine)){
            map<string, string> var;
            var["type"] = "Identifier";
            var["image"] = parsingArray[1];
            objectLine.push_back(var);

            map<string, string> op;
            op["type"] = "Operator";
            op["image"] = "=";
            objectLine.push_back(op);

            map<string, string> samevar;
            samevar["type"] = "Identifier";
            samevar["image"] = parsingArray[1];
            objectLine.push_back(samevar);

            map<string, string> multiply;
            multiply["type"] = "Operator";
            multiply["image"] = "*";
            objectLine.push_back(multiply);

            map<string, string> val;
            val["image"] = parsingArray[2];
            objectLine.push_back(val);

            mainObject.push_back(objectLine);
        }     
    }else if(regex_match(line, PowerLine)){
        if(regex_search(line, parsingArray, PowerLine)){
            map<string, string> var;
            var["type"] = "Identifier";
            var["image"] = parsingArray[1];
            objectLine.push_back(var);

            map<string, string> op;
            op["type"] = "Operator";
            op["image"] = "=";
            objectLine.push_back(op);

            map<string, string> samevar;
            samevar["type"] = "Identifier";
            samevar["image"] = parsingArray[1];
            objectLine.push_back(samevar);

            map<string, string> power;
            power["type"] = "Operator";
            power["image"] = "**";
            objectLine.push_back(power);

            map<string, string> val;
            val["type"] = "Operator";
            val["image"] = parsingArray[3];
            objectLine.push_back(val);

            mainObject.push_back(objectLine);
        }     
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

