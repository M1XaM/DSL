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

void tokenizeExpression(string expression, vector<Token>& lineObject){
    string str = "";
    int exp_length = expression.size();
    for(int i = 0; i < exp_length; i++){
        if(expression[i] == ' '){
            if(str.length() != 0){
                if(isInteger(str) || isFloat(str)){
                    lineObject.push_back(makeToken(TokenType::Number, str));
                }else{
                    lineObject.push_back(makeToken(TokenType::Identifier, str));
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
            lineObject.push_back(makeToken(TokenType::Number, str));
        }else{
            lineObject.push_back(makeToken(TokenType::Identifier, str));
        }
    }
}



void tokenizer(string line, int lineCount, vector<Token>& lineObject){

    regex EmptyLine("[\\s]*");
    regex CommentLine("[\\s]*#.*[\\s]*");
    regex ShowLine("[\\s]*show\\s+([a-zA-Z]\\w*)[\\s]*");

    regex InitializationLine("[\\s]*(int|float)\\s+([a-zA-Z]+)[\\s]*=[\\s]*([0-9]+(.[0-9]+)?)[\\s]*");
    regex AssigmentLine("\\s*([a-zA-Z]\\w*)\\s*=\\s*(.*)\\s*");
    regex OperationLine("\\s*([a-zA-Z]\\w*)\\s*(\\+|-|\\*|/|\\*\\*)=\\s*(.*)\\s*");

    regex LoopLine("[\\s]*for\\s+([a-zA-Z]\\w*)\\s+to\\s+([a-zA-Z_]\\w*|\\d+)\\s+repeat[\\s]*");
    regex ConditionalLine("[\\s]*if\\s+([a-zA-Z_]\\w*|\\d+(\\.\\d+)?|\\.\\d+)\\s+(>|<|==|!=|>=|<=)\\s+([a-zA-Z_]\\w*|\\d+(\\.\\d+)?|\\.\\d+)\\s+then[\\s]*");
    regex WrongDataType("[\\s]*var\\s+int\\s+([a-zA-Z_]+)[\\s]*=[\\s]*([0-9]+(\\.([0-9]+)?)?)[\\s]*");

    
    smatch parsingArray;
    if(regex_match(line, CommentLine)){
    }else if(regex_match(line, EmptyLine)){

    }else if(regex_match(line, InitializationLine)){
        if(regex_search(line, parsingArray, InitializationLine)){
            lineObject.push_back(makeToken(TokenType::Init, parsingArray[1]));
            lineObject.push_back(makeToken(TokenType::Identifier, parsingArray[2]));
            lineObject.push_back(makeToken(TokenType::Equal, "="));
            lineObject.push_back(makeToken(TokenType::Number, parsingArray[3]));
        }

    }else if(regex_match(line, ShowLine)){
        if(regex_search(line, parsingArray, ShowLine)){
            lineObject.push_back(makeToken(TokenType::Show, "show"));
            lineObject.push_back(makeToken(TokenType::Identifier, parsingArray[1]));
        }

    }else if(regex_match(line, AssigmentLine)){
        if(regex_match(line, parsingArray, AssigmentLine)){
            lineObject.push_back(makeToken(TokenType::Identifier, parsingArray[1]));
            lineObject.push_back(makeToken(TokenType::Equal, "="));
            
            string expression = parsingArray[2].str();
            tokenizeExpression(expression, lineObject);

        }
    }else if(regex_match(line, OperationLine)){
        if(regex_search(line, parsingArray, OperationLine)){
            lineObject.push_back(makeToken(TokenType::Identifier, parsingArray[1]));
            lineObject.push_back(makeToken(TokenType::Equal, "="));
            lineObject.push_back(makeToken(TokenType::Identifier, parsingArray[1]));
            lineObject.push_back(makeToken(whichTokenType(parsingArray[2].str()), parsingArray[2]));
            lineObject.push_back(makeToken(TokenType::OpenParen, "("));

            string expression = parsingArray[3].str();
            tokenizeExpression(expression, lineObject);

            lineObject.push_back(makeToken(TokenType::CloseParen, ")"));
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

