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
//     return root;
// }




// Node* mathExpression(vector<Token>& lineObject){
//     Node* root = createNode(lineObject[0]);
//     lineObject.erase(lineObject.begin());

//     while(!lineObject.empty()){
//         Node* workingNode = createNode(lineObject[0]);
//         lineObject.erase(lineObject.begin());
//         Node* parentNode = root;
//         Node* previousNode = nullptr;

//         if(workingNode->type == TokenType::CloseParen){  // If close paratheses - we have to return to the main tree
//             return root;
//         }

//         while(true){
//             if(workingNode->priority > parentNode->priority){  // See if go deeper
//                 if(parentNode->leftChild == nullptr){  // Try left subtree
//                     if(workingNode->type == TokenType::OpenParen){  // See if this are paratheses and make another tree
//                         parentNode->leftChild = mathExpression(lineObject);
//                         parentNode->leftChild->priority = static_cast<int>(TokenType::OpenParen);
//                        break;
//                     }else{  // Just go on left subtree
//                         parentNode->leftChild = workingNode;
//                         break;
//                     }
//                 }else if(parentNode->rightChild == nullptr){  // Try right subtree
//                     if(workingNode->type == TokenType::OpenParen){  // See if this are paratheses and make another tree

//                         parentNode->rightChild = mathExpression(lineObject); 
//                         parentNode->rightChild->priority = static_cast<int>(TokenType::OpenParen);
//                         break;
//                     }else{  // Just go on right subtree
//                         parentNode->rightChild = workingNode;
//                         break;
//                     }
//                 }else{  // Just go deeper
//                     cout << "one down" << endl;
//                     previousNode = parentNode;
//                     parentNode = parentNode->rightChild;
//                 }


//             }else if(workingNode->priority <= parentNode->priority){  // Find his place, begin to switch
//                 if(previousNode == nullptr){  // We are on root node
//                     if(root->leftChild == nullptr){  // Try left subtree
//                         Node* tempNode = root;
//                         root = workingNode;
//                         root->leftChild = tempNode;
//                         break;
//                     }else if(root->rightChild == nullptr){  // Try right subtree
//                         Node* tempNode = root;
//                         root = workingNode;
//                         root->rightChild = tempNode;
//                         break;
//                     }else{  // 4 nodes in total and workingNode have smaller priority than root
//                         Node* tempNode = root;
//                         root = workingNode;
//                         root->leftChild = tempNode;
//                         break;
//                     }
//                 }else{  // We are not on root
//                     if(workingNode->type == TokenType::OpenParen){  // See if this are paratheses and make another tree
//                         previousNode->rightChild = mathExpression(lineObject);
//                         previousNode->rightChild->priority = static_cast<int>(TokenType::OpenParen);
//                         break;
//                     }else{  // Just switch
//                         previousNode->rightChild = workingNode;
//                         previousNode->rightChild->leftChild = parentNode;
//                         break;
//                     }
//                 }
//             }
//         }
//     }
//     return root;
// }

Node* mathExpression(vector<Token>& lineObject);
void timeToSwitch(vector<Token>& lineObject, Node* root, Node* workingNode, Node* parentNode, Node* previousNode){
                if(previousNode == nullptr){  // We are on root node
                    if(root->leftChild == nullptr){  // Try left subtree
                        Node* tempNode = root;
                        root = workingNode;
                        root->leftChild = tempNode;
                        return;
                    }else if(root->rightChild == nullptr){  // Try right subtree
                        Node* tempNode = root;
                        root = workingNode;
                        root->rightChild = tempNode;
                        return;
                    }else{  // 4 nodes in total and workingNode have smaller priority than root
                        Node* tempNode = root;
                        root = workingNode;
                        root->leftChild = tempNode;
                        return;
                    }
                }else{  // We are not on root
                    if(workingNode->type == TokenType::OpenParen){  // See if this are paratheses and make another tree
                        previousNode->rightChild = mathExpression(lineObject);
                        previousNode->rightChild->priority = static_cast<int>(TokenType::OpenParen);
                        return;
                    }else{  // Just switch
                        previousNode->rightChild = workingNode;
                        previousNode->rightChild->leftChild = parentNode;
                        return;
                    }
                }
}

void goDeeper(vector<Token>& lineObject, Node* root, Node* workingNode, Node* parentNode, Node* previousNode){
                if(parentNode->leftChild == nullptr){  // Try left subtree
                    if(workingNode->type == TokenType::OpenParen){  // See if this are paratheses and make another tree

                        

                        parentNode->leftChild = mathExpression(lineObject);
                        parentNode->leftChild->priority = static_cast<int>(TokenType::OpenParen);
                        return;
                    }else{  // Just go on left subtree
                        parentNode->leftChild = workingNode;
                        return;
                    }
                }else if(parentNode->rightChild == nullptr){  // Try right subtree
                    if(workingNode->type == TokenType::OpenParen){  // See if this are paratheses and make another tree

                        

                        parentNode->rightChild = mathExpression(lineObject); 
                        parentNode->rightChild->priority = static_cast<int>(TokenType::OpenParen);
                        return;
                    }else{  // Just go on right subtree
                        parentNode->rightChild = workingNode;
                        return;
                    }
                }else{  // Just go deeper
                    previousNode = parentNode;
                    parentNode = parentNode->rightChild;
                }                
}

Node* mathExpression(vector<Token>& lineObject){
    for(int i = 0; i < lineObject.size(); i++){
        cout << lineObject[i].value;
    }
    cout << endl;

    Node* root = createNode(lineObject[0]);
    lineObject.erase(lineObject.begin());

    while(!lineObject.empty()){
        Node* workingNode = createNode(lineObject[0]);
        lineObject.erase(lineObject.begin());
        Node* parentNode = root;
        Node* previousNode = nullptr;

        if(workingNode->type == TokenType::CloseParen){  // If close paratheses - we have to return to the main tree
            return root;
        }

        while(true){
            if(workingNode->priority > parentNode->priority){  // See if go deeper
                goDeeper(lineObject, root, workingNode, parentNode, previousNode);
            }else if(workingNode->priority <= parentNode->priority){  // Find his place
                timeToSwitch(lineObject, root, workingNode, parentNode, previousNode);
            }
        }
    }
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

        // cout << root->leftChild->rightChild->value << " " << int(root->leftChild->rightChild->type)<< endl;
        // cout << root->leftChild->rightChild->rightChild->value << endl;
    }else{
        root = mathExpression(lineObject);
        // cout << root->value << endl;
        // cout << root->leftChild->value << endl;
        // cout << root->rightChild->value << endl;
        // cout << root->rightChild->leftChild->value << endl;
        // cout << root->rightChild->rightChild->value << endl; // this must be the 3 but its close paranthes
        // cout << root->rightChild->rightChild->rightChild->value << endl;

        
    }
    return root;
}
