#include<iostream>
#include<string>
#include<vector>
#include<regex>
using namespace std;

enum class TokenType{
    If = 5, Init = 6, Show = 7,
    Equal = 8,
    Plus = 9, Minus = 9,
    Multiply = 10, Divide = 10,
    Power = 11,
    Number = 12, Identifier = 12,
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

bool isOperator(string str){
    string plus = "+";
    string minus = "-";
    string multiplication = "*";
    string division = "/";
    
    return str == plus || str == minus || str == multiplication || str == division;
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
                }else if(isOperator(str)){
                    lineObject.push_back(makeToken(whichTokenType(str), str));
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

    regex ShowLine("[\\s]*show\\s+(.*)[\\s]*");
    regex InitializationLine("[\\s]*(int|float)\\s+([a-zA-Z]+)[\\s]*=[\\s]*(.*)[\\s]*"); // modified
    regex AssigmentLine("\\s*([a-zA-Z]\\w*)\\s*=\\s*(.*)\\s*");

    regex ConditionalLine("[\\s]*if\\s+([a-zA-Z_]*)[\\s]*=[\\s]*(.*)\\s+then[\\s]*");
    regex ConditionalLineEnd("[\\s]*endif[\\s]*");
;    // regex LoopLine("[\\s]*for\\s+([a-zA-Z]\\w*)\\s+to\\s+([a-zA-Z_]\\w*|\\d+)\\s+repeat[\\s]*");

    
    smatch parsingArray;
    if(regex_match(line, CommentLine)){
    }else if(regex_match(line, EmptyLine)){
    }else if(regex_match(line, InitializationLine)){
        if(regex_search(line, parsingArray, InitializationLine)){
            lineObject.push_back(makeToken(TokenType::Init, parsingArray[1]));
            lineObject.push_back(makeToken(TokenType::Identifier, parsingArray[2]));
            lineObject.push_back(makeToken(TokenType::Equal, "="));
            // lineObject.push_back(makeToken(TokenType::Number, parsingArray[3]));

            string expression = parsingArray[3].str();
            tokenizeExpression(expression, lineObject);
        }

    }else if(regex_match(line, ShowLine)){
        if(regex_search(line, parsingArray, ShowLine)){
            lineObject.push_back(makeToken(TokenType::Show, "show"));
            // lineObject.push_back(makeToken(TokenType::Identifier, parsingArray[1]));

            string expression = parsingArray[1].str();
            tokenizeExpression(expression, lineObject);            
        }

    }else if(regex_match(line, AssigmentLine)){
        if(regex_search(line, parsingArray, AssigmentLine)){
            lineObject.push_back(makeToken(TokenType::Identifier, parsingArray[1]));
            lineObject.push_back(makeToken(TokenType::Equal, "="));
            
            string expression = parsingArray[2].str();
            tokenizeExpression(expression, lineObject);

        }
    }else if(regex_match(line, ConditionalLine)){
        if(regex_search(line, parsingArray, ConditionalLine)){
            lineObject.push_back(makeToken(TokenType::If, "if"));
            lineObject.push_back(makeToken(TokenType::Identifier, parsingArray[1]));
            lineObject.push_back(makeToken(TokenType::Equal, "="));
            // lineObject.push_back(makeToken(TokenType::Number, parsingArray[2]));
            
            string expression = parsingArray[2].str();
            tokenizeExpression(expression, lineObject);

        }
    }else if(regex_match(line, ConditionalLineEnd)){
        if(regex_search(line, parsingArray, ConditionalLineEnd)){
            lineObject.push_back(makeToken(TokenType::If, "endif"));
        }

    // }else if(regex_match(line, LoopLine)){
    }else{
        cout << "Syntax Error (on line number " << lineCount << ")" << endl;
        exit(1);
    }
}

