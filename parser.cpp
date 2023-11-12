#include<iostream>
#include<vector>
#include<string>
using namespace std;

enum class TokenType{
    Init = 1, Show = 2,
    Equal = 3,
    Plus = 4, Minus = 4,
    Multiply = 5, Divide = 5,
    Power = 6,
    Number = 7, Identifier = 7,
    OpenParen = 8, CloseParen = 9,
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
};

void clearTree(Node* root){
    // cout << root->value << endl;
    if(root->leftChild == nullptr && root->rightChild == nullptr){
        delete root;
        return;
    }
    if(root->leftChild != nullptr){
        clearTree(root->leftChild);
    }
    if(root->rightChild != nullptr){
        clearTree(root->rightChild);
    }
}

Node* createNode(Token token){
    Node* newNode = new Node();
    newNode->type = token.type;
    newNode->value = token.value;
    newNode->leftChild = nullptr;
    newNode->rightChild = nullptr;
    newNode->priority = static_cast<int>(token.type);
    return newNode;
}

// Node* mathExpression(vector<Token>& lineObject){
//     Node* root = createNode(lineObject[0]);

//     for(int i = 1; i < lineObject.size(); i++){
//         Node* workingNode = createNode(lineObject[i]);
//         Node* parentNode = root;
//         Node* previousNode = nullptr;
//         while(true){
//             if(workingNode->priority > parentNode->priority){
//                 if(parentNode->leftChild == nullptr){
//                     parentNode->leftChild = workingNode;
//                     break;
//                 }else if(parentNode->rightChild == nullptr){
//                     parentNode->rightChild = workingNode;
//                     break;
//                 }else{
//                     previousNode = parentNode;
//                     parentNode = parentNode->rightChild;
//                 }
//             }else if(workingNode->priority <= parentNode->priority){
//                 if(previousNode == nullptr){ // we are on root node
//                     if(root->leftChild == nullptr){
//                         Node* tempNode = root;
//                         root = workingNode;
//                         root->leftChild = tempNode;
//                         break;
//                     }else if(root->rightChild == nullptr){
//                         Node* tempNode = root;
//                         root = workingNode;
//                         root->rightChild = tempNode;
//                         break;
//                     }else{
//                         previousNode = parentNode;
//                         parentNode = parentNode->rightChild;
//                     }
//                 }else{
                    
//                     previousNode->leftChild = workingNode;
//                     previousNode->leftChild->rightChild = parentNode;
//                 }
//                 break;
//             }
            
//         }   
//     }

//     // cout << root->leftChild->value << endl;
//     // cout << root->rightChild << endl;
//     return root;
// }

// Node* parenthesesStart(vector<Token>& lineObject){

// }

// Function that modifies a vector and retains only the specified range
void cutVectorRange(vector<Token>& vec, int startIndex, int endIndex) {
    // Ensure that the indices are within bounds
    startIndex = std::max(0, startIndex);
    endIndex = std::min(static_cast<int>(vec.size()), endIndex);

    // Erase elements outside the specified range
    vec.erase(vec.begin() + endIndex, vec.end());
    vec.erase(vec.begin(), vec.begin() + startIndex);
}

vector<Token> cutThisShit(vector<Token>& lineObject, int start, int end){
    vector<Token> newVec;
    for(int i = start; i <= end; i++){
        newVec.push_back(lineObject[i]);
    }
    return newVec;
}

Node* mathExpression(vector<Token>& lineObject){
    Node* root = createNode(lineObject[0]);
    for(int i = 1; i < lineObject.size(); i++){
    // while(static_cast<int>(lineObject.size()) > 0){
    // do{
        Node* workingNode = createNode(lineObject[i]);
        Node* parentNode = root;
        Node* previousNode = nullptr;

        if(workingNode->type == TokenType::CloseParen){
            // cutVectorRange(lineObject, 1, lineObject.size());
            // lineObject = cutThisShit(lineObject, 1, lineObject.size());
            return root;
        }

        while(true){
            if(workingNode->priority > parentNode->priority){
                if(parentNode->leftChild == nullptr){
                    parentNode->leftChild = workingNode;
                    break;
                }else if(parentNode->rightChild == nullptr){
                    parentNode->rightChild = workingNode;
                    break;
                }else{
                    previousNode = parentNode;
                    parentNode = parentNode->rightChild;
                }
            }else if(workingNode->priority <= parentNode->priority){
                if(previousNode == nullptr){ // we are on root node
                    if(root->leftChild == nullptr){
                        Node* tempNode = root;
                        root = workingNode;
                        root->leftChild = tempNode;
                        break;
                    }else if(root->rightChild == nullptr){
                        Node* tempNode = root;
                        root = workingNode;
                        root->rightChild = tempNode;
                        break;
                    }else{
                        previousNode = parentNode;
                        parentNode = parentNode->rightChild;
                    }
                }else{
                    if(workingNode->type == TokenType::OpenParen){
                        // cutVectorRange(lineObject, 1, lineObject.size());
                        lineObject = cutThisShit(lineObject, 1, lineObject.size());
                        previousNode->leftChild = mathExpression(lineObject);
                        previousNode->leftChild->priority = static_cast<int>(TokenType::OpenParen);
                    }else{
                        previousNode->leftChild = workingNode;
                        previousNode->leftChild->rightChild = parentNode;
                    }
                }
                break;
            }
        }
        // cutVectorRange(lineObject, 1, lineObject.size()); 
        // lineObject.erase(lineObject.begin());
        // lineObject = cutThisShit(lineObject, 1, lineObject.size());
    }
    // }while(static_cast<int>(lineObject.size()) > 0);
    return root;
}

Node* makeTree(vector<Token>& lineObject){
    Node* root = createNode(lineObject[0]);
    if(root->type == TokenType::Show){
        root->leftChild = createNode(lineObject[1]); // we can show just the variables
    }else if(root->type == TokenType::Init){
        
        lineObject.erase(lineObject.begin());
        root->leftChild = mathExpression(lineObject);
        // cout << root->value << " " << int(root->type) << endl;
        // cout << root->leftChild->value << " " << int(root->leftChild->type) << endl;
        // cout << root->leftChild->leftChild->value << " " << int(root->leftChild->leftChild->type) << endl;
        // cout << root->leftChild->leftChild->leftChild->value << " " << int(root->leftChild->leftChild->leftChild->type) << endl;
        // cout << root->leftChild->leftChild->rightChild->value << " " << int(root->leftChild->leftChild->leftChild->leftChild->type) << endl;
        // cout << endl;

        // cout << root->leftChild->rightChild->value << endl;
        // cout << root->leftChild->rightChild->rightChild->value << endl;
    }else{
        root = mathExpression(lineObject);
    }
    return root;
}
