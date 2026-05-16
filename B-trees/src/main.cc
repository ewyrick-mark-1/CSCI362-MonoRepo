#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <queue>

using namespace std;

const int N_MAX = 400;
const int B = 5; //how wide a node can be
const int MIN_KEYS = (B + 1) / 2 - 1; 

struct Node
{
    Node *father = nullptr;
    vector<int> keys;
    vector<Node*> branches;
    bool isLeaf;

    Node(bool leaf = true) : isLeaf(leaf) {}
};

struct Insert_Return_Value
{
    Node *left = nullptr;
    Node *right = nullptr;
    int key;

    Insert_Return_Value(int key, Node *left, Node *right) : key(key), left(left), right(right) {};
};

void generateKeys(int N, vector<int>& keys){
    for(int i = 0; i < N; i++){
        int random_key = rand() % ((3*N )+ 1);
        keys.push_back(random_key);
    }

    cout << "generated keys: ";
    for(int i = 0; i < keys.size(); i++){
        cout << keys[i];
        if(i < keys.size() - 1) cout << ", ";
    }
    cout << endl;
}

void addSorted(vector<int>& vec, int key){
    for(int i = 0; i < vec.size(); i++){
        if(key <= vec[i]){
            vec.insert(vec.begin() + i, key);
            return;
        }
    }
    vec.push_back(key);
}

//--------------insert block---------------
Insert_Return_Value* insert(Node *node, int key){
    int max_keys = B - 1;
    Insert_Return_Value* RV = nullptr;

    if(!node->isLeaf){
        int i = 0;
        while(i < node->keys.size() && key > node->keys[i]){
            i++;
        }
        RV = insert(node->branches[i], key);

        if(RV == nullptr){
            return nullptr;
        }
        key = RV->key;
    }

    if(node->keys.size() < max_keys){
        // no overflow
        addSorted(node->keys, key);

        if(RV != nullptr){
            int i = 0;
            while(i < node->keys.size() && key > node->keys[i]){
                i++;
            }
            node->branches.insert(node->branches.begin() + i + 1, RV->right);
            RV->right->father = node;
        }
        return nullptr;
    }

    // Overflow- need to split
    vector<int> temp = node->keys;
    addSorted(temp, key);

    vector<Node*> temp_children = node->branches;
    if(RV != nullptr){
        int i = 0;
        while(i < temp.size() && key > temp[i]){
            i++;
        }
        temp_children.insert(temp_children.begin() + i + 1, RV->right);
    }

    int mid_index = B / 2;
    int promoted_key = temp[mid_index];


    Node* left_node = new Node(node->isLeaf);
    Node* right_node = new Node(node->isLeaf);

    left_node->keys.assign(temp.begin(), temp.begin() + mid_index);
    right_node->keys.assign(temp.begin() + mid_index + 1, temp.end());

    if(!node->isLeaf){
        left_node->branches.assign(temp_children.begin(), temp_children.begin() + mid_index + 1);
        right_node->branches.assign(temp_children.begin() + mid_index + 1, temp_children.end());

        // Update fathers
        for(Node* child : left_node->branches){
            child->father = left_node;
        }
        for(Node* child : right_node->branches){
            child->father = right_node;
        }
    }

    left_node->father = node->father;
    right_node->father = node->father;

    node->keys = left_node->keys;
    node->branches = left_node->branches;

    return new Insert_Return_Value(promoted_key, node, right_node);
}

//--------------visualize------------------
void visualizeTree(Node* root){
    if(root == nullptr){
        cout << "Empty tree" << endl;
        return;
    }

    queue<Node*> q;
    q.push(root);
    int level = 0;

    cout << "\nB-Tree:" << endl;

    while(!q.empty()){
        int nodes_at_level = q.size();
        cout << "level " << level << ": ";

        for(int i = 0; i < nodes_at_level; i++){
            Node* current = q.front();
            q.pop();

            // Print node keys
            cout << "[";
            for(int j = 0; j < current->keys.size(); j++){
                cout << current->keys[j];
                if(j < current->keys.size() - 1) cout << ",";
            }
            cout << "]";

            cout << "  ";

            // Add children to queue
            for(Node* child : current->branches){
                q.push(child);
            }
        }
        cout << endl;
        level++;
    }
}

//--------------range search block-----------
void rangeSearchHelper(Node* node, int min, int max, vector<int>& results){
    if(node == nullptr) return;

    int i = 0;

    for(i = 0; i < node->keys.size(); i++){
        if(!node->isLeaf && node->keys[i] >= min){
            rangeSearchHelper(node->branches[i], min, max, results);
        }

        // Add key
        if(node->keys[i] >= min && node->keys[i] <= max){
            results.push_back(node->keys[i]);
        }

        if(node->keys[i] > max){
            return;
        }
    }

    if(!node->isLeaf && i < node->branches.size()){
        rangeSearchHelper(node->branches[i], min, max, results);
    }
}

vector<int> rangeSearch(Node* root, int min, int max){
    vector<int> results;
    rangeSearchHelper(root, min, max, results);
    return results;
}

//---------------- build tree (uses insert)------
void buildTree(Node*& root, vector<int> random_keys){
    for(int i = 0; i < random_keys.size(); i++){
        int key = random_keys[i];
        Insert_Return_Value* result = insert(root, key);

        // Check if root split - need to create new root
        if(result != nullptr){
            Node* new_root = new Node(false); // Internal node
            new_root->keys.push_back(result->key);
            new_root->branches.push_back(result->left);
            new_root->branches.push_back(result->right);

            result->left->father = new_root;
            result->right->father = new_root;

            root = new_root;
        }
    }
}

int main() {

    srand((int)time(0));

    int N;
    cin >> N;

    // Check N does not exceed 400
    if(N > N_MAX){
        cout << "Error: N cannot exceed " << N_MAX << endl;
        return 1;
    }

    vector<int> random_keys;

    generateKeys(N, random_keys);

    Node* root = new Node(true); // Start with leaf

    if(random_keys.empty()) return 1;

    buildTree(root, random_keys);

    cout << "tree built" << endl;
    visualizeTree(root);

    cout << "\nrange Search [" << N << ", " << 2*N << "]" << endl;
    vector<int> rangeResults = rangeSearch(root, N, 2*N);

    cout << "keys found in range: ";
    if(rangeResults.empty()){
        cout << "none";
    } else {
        for(int i = 0; i < rangeResults.size(); i++){
            cout << rangeResults[i];
            if(i < rangeResults.size() - 1) cout << ", ";
        }
    }
    cout << endl;

    return 0;
}