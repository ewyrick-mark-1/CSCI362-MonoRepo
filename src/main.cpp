#include <iostream>
#include <cmath>
#include <vector>
#include <stack>
#include <array>

using namespace std;

static int input[] = {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9};
//static int input[] = {};
static int input_length = sizeof(input)/sizeof(input[0]);

struct Node
{
    int key;
    int height;
    Node *left = nullptr;
    Node *right = nullptr;
    Node(int key_input) : key(key_input) {};
};

int getHeight(Node* node){
    if(node){
        return node->height;
    }
    return 0;
}

void updateHeight(Node* node){
    if(node){
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }

}

int getBalace(Node* node){
    if(node){
        return getHeight(node->left) - getHeight(node->right);
    }
    return 0;
}

Node* rotateLeft(Node* x) {
    if (!x || !x->right) return x;

    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node* rotateRight(Node* y) {
    if (!y || !y->left) return y;

    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* insertKey(Node *node, int key){
    
    //bottom of recursion. add leaf with key.
    if(!node){
        Node* new_node = new  Node(key);
        new_node->height = 1;
        return new_node;
    }

    //recursion calls to walk the tree.  O(n)
    if (key > node->key) node->right = insertKey(node->right, key);
    else if (key < node->key) node->left = insertKey(node->left, key);
    else return node;

    //update the height of the node
    updateHeight(node);

    //determine balance and rotate tree if unbalanced
    int balance = getBalace(node);

    //left left
    if(balance > 1 && key < node->left->key){
        return rotateRight(node);
    }

    //right right
    if(balance < -1 && key > node->right->key){
        return rotateLeft(node);
    }

    //left right
    if(balance > 1 && key > node->left->key){
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    //right left
    if(balance < -1 && key < node->right->key){
        node->right = rotateLeft(node->right);
        return rotateLeft(node);
    }

    //balanced
    return node;
}

Node* minValueNode(Node* node){
    Node* current = node;
    while(current && current->left != nullptr){
        current = current->left;
    }
    return current;
}

Node* deleteKey(Node *node, int key){
    if(!node) return nullptr;

    if(key < node->key){
        node->left = deleteKey(node->left, key);
    } 
    else if(key > node->key){
        node->right = deleteKey(node->right, key);
    } 
    else {


        //one child or no child
        if(!node->left){
            Node* temp = node->right;
            delete node;
            return temp;
        } 
        else if(!node->right){
            Node* temp = node->left;
            delete node;
            return temp;
        }

        //two children
        Node* temp = minValueNode(node->right);
        node->key = temp->key;
        node->right = deleteKey(node->right, temp->key);
    }

    //update height
    updateHeight(node);

    //get balance
    int balance = getBalace(node);

    //rebalance

    // Left Left
    if(balance > 1 && getBalace(node->left) >= 0){
        return rotateRight(node);
    }

    // Left Right
    if(balance > 1 && getBalace(node->left) < 0){
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Right
    if(balance < -1 && getBalace(node->right) <= 0){
        return rotateLeft(node);
    }

    // Right Left
    if(balance < -1 && getBalace(node->right) > 0){
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void printTreeHelper(Node* node, int height){
    if(!node){
        return;
    }

    if(node->height == height) printf(  "%d  ", node->key);
    printTreeHelper(node->left, height);
    printTreeHelper(node->right, height);
    return;
}

void printTree(Node* node){
    if(!node){
        return;
    }

    for(int i = node->height; i > 0; i--){
        printf("   Height : %d, Keys : ", i);
        printTreeHelper(node, i);
        printf("\n");
    }
    
    return;
}

int main(){
    Node* root = new Node(input[0]);

    for(int i = 1; i < input_length; i++){
        root = insertKey(root, input[i]);
    }
    printf("   Tree:\n");
    printTree(root);
    printf("\n");
    
    //user input loop & parsing
    
    string user_input;
    int key;

    printf("   commands:\n   <add/delete> <key>\n   print\n   exit\n");
    while(user_input != "exit"){
        printf(">> ");
        cin >> user_input;

        if (user_input == "add") {
            cin >> key;
            root = insertKey(root, key);
            printf("   Inserted %d (if it was not there before)\n", key);
        } 
        else if (user_input == "delete") {
            cin >> key;
            root = deleteKey(root, key);
            printf("   Deleted %d (if it existed)\n", key);
        } 
        else if (user_input == "print") {
            printf("   Tree:\n");
            printTree(root);
        } 
        else if (user_input == "exit") {
            printf("   Exiting...\n");
            break;
        }
        else {
            printf("   Unknown command.\n");
            // clear any remaining junk input
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    }
    
    return 0;
}
