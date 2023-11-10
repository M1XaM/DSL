#include<iostream>
#include<string>
#include<vector>
#include<regex>
using namespace std;

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

TokenType whichTokenType(string sign){
    TokenType result;
    switch(sign[0]){
        case '+':
            result = TokenType::Plus;
            break;
        case '-':
            result = TokenType::Minus;
            break;
        case '*':
            result = TokenType::Multiply;
                break;
        case '/':
            result = TokenType::Divide;
            break;
        }
    return result;
    }



bool isInteger(const std::string& s){
    if(s.empty() || (!isdigit(s[0]) && s[0] != '-' && s[0] != '+')){
        return false;
    }
    char* endPtr;
    strtol(s.c_str(), &endPtr, 10);
    return (*endPtr == '\0');
}

bool isFloat(const std::string& s){
    if(s.empty() || (!isdigit(s[0]) && s[0] != '-' && s[0] != '+')){
        return false;
    }

    char* endPtr;
    strtof(s.c_str(), &endPtr);
    return (*endPtr == '\0');
}

bool isValidVariableName(const std::string& s){
    if(s.empty() || !isalpha(s[0])){
        return false;
    }
    for(char c : s){
        if(!isalnum(c)){
            return false;
        }
    }
    return true;
}

Token makeToken(TokenType type_arg, string value_arg){
    Token token = { .type = type_arg, .value = value_arg,};
    return token;
}

void tokenizeExpression(string expression, vector<Token>& objectLine, vector<vector<Token>>& mainObject){
    string str = "";
    int exp_length = expression.size();
    for(int i = 0; i < exp_length; i++){
        if(expression[i] == ' '){
            if(str.length() != 0){
                if(isInteger(str) || isFloat(str)){
                    objectLine.push_back(makeToken(TokenType::Number, str));
                }else{
                    objectLine.push_back(makeToken(TokenType::Identifier, str));
                }
                str = "";
            }
        }else{
            str += expression[i];
        }
    }

    // Check and tokenize the last substring if it's not empty
    if(str.length() != 0){
        if(isInteger(str) || isFloat(str)){
            objectLine.push_back(makeToken(TokenType::Number, str));
        }else{
            objectLine.push_back(makeToken(TokenType::Identifier, str));
        }
    }
}



void tokenizer(string line, int lineCount, vector<vector<Token>>& mainObject){

    regex EmptyLine("[\\s]*");
    regex CommentLine("[\\s]*#.*[\\s]*");
    regex ShowLine("[\\s]*show\\s+([a-zA-Z]\\w*)[\\s]*");

    regex InitializationLine("[\\s]*(int|float)\\s+([a-zA-Z]+)[\\s]*=[\\s]*([0-9]+)[\\s]*");
    regex AssigmentLine("\\s*([a-zA-Z]\\w*)\\s*=\\s*(.*)\\s*");
    regex OperationLine("\\s*([a-zA-Z]\\w*)\\s*(\\+|-|\\*|/|\\*\\*)=\\s*(.*)\\s*");

    regex LoopLine("[\\s]*for\\s+([a-zA-Z]\\w*)\\s+to\\s+([a-zA-Z_]\\w*|\\d+)\\s+repeat[\\s]*");
    regex ConditionalLine("[\\s]*if\\s+([a-zA-Z_]\\w*|\\d+(\\.\\d+)?|\\.\\d+)\\s+(>|<|==|!=|>=|<=)\\s+([a-zA-Z_]\\w*|\\d+(\\.\\d+)?|\\.\\d+)\\s+then[\\s]*");
    regex WrongDataType("[\\s]*var\\s+int\\s+([a-zA-Z_]+)[\\s]*=[\\s]*([0-9]+(\\.([0-9]+)?)?)[\\s]*");

    vector<Token> objectLine;
    smatch parsingArray;
    if(regex_match(line, CommentLine)){
    }else if(regex_match(line, EmptyLine)){

    }else if(regex_match(line, InitializationLine)){
        if(regex_search(line, parsingArray, InitializationLine)){
            objectLine.push_back(makeToken(TokenType::Init, parsingArray[1]));
            objectLine.push_back(makeToken(TokenType::Identifier, parsingArray[2]));
            objectLine.push_back(makeToken(TokenType::Equal, "="));
            objectLine.push_back(makeToken(TokenType::Number, parsingArray[3]));
            mainObject.push_back(objectLine);
        }

    }else if(regex_match(line, ShowLine)){
        if(regex_search(line, parsingArray, ShowLine)){
            objectLine.push_back(makeToken(TokenType::Show, "show"));
            objectLine.push_back(makeToken(TokenType::Identifier, parsingArray[1]));
            mainObject.push_back(objectLine);
        }

    }else if(regex_match(line, AssigmentLine)){
        if(regex_match(line, parsingArray, AssigmentLine)){
            objectLine.push_back(makeToken(TokenType::Identifier, parsingArray[1]));
            objectLine.push_back(makeToken(TokenType::Equal, "="));
            
            string expression = parsingArray[2].str();
            tokenizeExpression(expression, objectLine, mainObject);

            mainObject.push_back(objectLine);
        }
    }else if(regex_match(line, OperationLine)){
        if(regex_search(line, parsingArray, OperationLine)){
            objectLine.push_back(makeToken(TokenType::Identifier, parsingArray[1]));
            objectLine.push_back(makeToken(TokenType::Equal, "="));
            objectLine.push_back(makeToken(TokenType::Identifier, parsingArray[1]));
            objectLine.push_back(makeToken(whichTokenType(parsingArray[2].str()), parsingArray[2]));
            objectLine.push_back(makeToken(TokenType::OpenParen, "("));

            string expression = parsingArray[3].str();
            tokenizeExpression(expression, objectLine, mainObject);

            objectLine.push_back(makeToken(TokenType::CloseParen, ")"));
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

