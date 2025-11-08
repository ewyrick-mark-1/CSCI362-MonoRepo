
#include <iostream>
#include <cmath>

#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()

using namespace std;

//struct for the hash node - basically a linked list.
struct hash_node {
    int value;
    hash_node* next_addr;
};

const int MAX_SIZE = 1000;
const int MIN_VALUE = 10;
const int MAX_VALUE = 99;

void generateRandomNumbers(int* arr, int arr_size){
    for(int i = 0; i < arr_size; i++){
        arr[i] = (rand() % (MAX_VALUE - MIN_VALUE + 1)) + MIN_VALUE;
    }
}

inline int hashFunction(int value){
    return value/10;
}

void mapValue(int value, hash_node*& addr){//pass a reference

    if(addr == nullptr){
        hash_node* Node = new hash_node;
        Node->value = value;
        addr = Node;
    }else{
        mapValue(value, addr->next_addr);

    }
}

void mapNumbers(int* arr, int arr_size, hash_node** map){
    //hash function each value assign each value somewhere in the hash table
    for(int i = 0; i < MAX_SIZE; i++){
        int random_number = arr[i];
        int hashed_number = hashFunction(random_number);
        //cout << "hashed " << random_number << " as " << hashed_number << endl;
        mapValue(random_number, map[hashed_number]);
        //cout << "value mapped!\n";
        
    }
}

void printLinkedList( hash_node* node){ 
    if(node != nullptr){
        cout << node->value << " " ;
        printLinkedList(node->next_addr);
    }
}

void printMap(hash_node** map){
    //assumes a linear hash
    for(int i = hashFunction(MIN_VALUE); i < hashFunction(MAX_VALUE) + 1; i ++){
        cout << "hash key: " << i <<endl;

        if(map[i] != nullptr){
            printLinkedList(map[i]);
        }
        cout << endl;
    }

}

bool deleteLinkedListValue(int value, hash_node*& node){
    //lot of reused code from clearLinkedListDuplicates. probably could consolidate it better
    if(node != nullptr){
        if(node->value == value){
            //found value - determine how to delete
            if(node->next_addr != nullptr){
                //remove node and check new one.
                int new_value = node->next_addr->value;
                hash_node* new_addr = node->next_addr->next_addr;
                node->value = new_value;
                node->next_addr = new_addr;
                return true;
            }else{
                //last node in the list, delete it.
                delete node; // clear memory
                node = nullptr; 
                return true; 
                
            }
            
        }else{
            //not the value, move along
            if(node->next_addr != nullptr){
                return deleteLinkedListValue(value, node->next_addr);
            
            }else{
                //end of the list, not found.
                return false;
            }
        } 
    }else{
        //empty list 
        return false;
    }
    
}

bool deleteValue(int value, hash_node** map){
    
    int hash_value = hashFunction(value);
    //cout<< "clearing " << i <<endl;
    //recursively look through the linked list for the value to be deleted.
    return deleteLinkedListValue(value, map[hash_value]);
    //cout <<"cleared " << i << endl;
        
}

void clearLinkedListDuplicates(int value, hash_node*& node, bool exists){

    if(node != nullptr){
        if(node->value == value){
            if(exists){
                if(node->next_addr != nullptr){
                    //duplicate, remove node and check new one.
                    int new_value = node->next_addr->value;
                    hash_node* new_addr = node->next_addr->next_addr;
                    node->value = new_value;
                    node->next_addr = new_addr;
                    clearLinkedListDuplicates(value, node, exists);
                }else{
                    //duplicate and last node in the list, delete it.
                    delete node; // clear memory
                    node = nullptr; 
                    
                }
            }else{
                //is the value, first time seeing. keep the value and update exists
                if(node->next_addr != nullptr){
                    clearLinkedListDuplicates(value, node->next_addr, true);
                }
            }
        }else{
            //not the value, move along
            if(node->next_addr != nullptr){
                clearLinkedListDuplicates(value, node->next_addr, exists);
            
            }
        } 
    }
}

void clearDuplicates(hash_node** map){
    for(int i = MIN_VALUE; i < MAX_VALUE + 1; i ++){
        int hash_value = hashFunction(i);
        //cout<< "clearing " << i <<endl;
        //recursively look through the linked list for occurrences of this value.
        clearLinkedListDuplicates(i, map[hash_value], false);
        //cout <<"cleared " << i << endl;
    }
}

bool searchLinkedList(int value, hash_node*& node){
    if(node != nullptr){
        if(node->value == value){
            //value found
            return true;
        }else{
            //not the correct value, check the next one
            return searchLinkedList(value, node->next_addr);
        }
    }else{
        //not found, at end of list
        return false;
    }
}

inline bool isValid(int n){
    return (n >= MIN_VALUE && n <= MAX_VALUE) ? true : false;
}

bool isValidHash(int n){
    return (n >= hashFunction(MIN_VALUE) && n <= hashFunction(MAX_VALUE)) ? true : false;
}
void userInput(hash_node** table){
    bool isRunning = true; 
    while(isRunning){

        char input;
        cout << "enter a command:\n[i : insert, d : delete, s : search, c : clear duplicates p : print, e : exit]\n";
        cin >> input;

        if(input == 'i'){

            int num_input;
            cout << "enter number to insert:\n";

            while (!(cin >> num_input)) { // Loop until valid integer input
                cout << "Invalid input. Please enter an integer:\n";
                cin.clear(); // Clear the error state of cin
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Discard remaining invalid input
            }
            if(isValid(num_input)){
                mapValue(num_input, table[hashFunction(num_input)]);
            }else{
                cout << "invalid input. value must greater than " << MIN_VALUE << " and less than " << MAX_VALUE << endl;
            }
            

        }else if (input == 'd'){

            int num_input;
            cout << "enter number to delete:\n";

            //while loop to make sure proper value is entered
            while (!(cin >> num_input)) { // Loop until valid integer input
                cout << "Invalid input. Please enter an integer:\n";
                cin.clear(); // Clear the error state of cin
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Discard remaining invalid input
            }
            if(isValid(num_input)){
                bool isDeleted = deleteValue(num_input, table);

                if(isDeleted){
                    cout<< "deleted " << num_input << endl;
                }else{
                    cout<< "could not find: " << num_input << endl;
                }
            }else{
                //nonvalid input - outside range
                cout << "invalid input. value must greater than " << MIN_VALUE << " and less than " << MAX_VALUE << endl;
            }
            
        }else if (input == 's'){

            int num_input;
            cout << "enter number to search:\n";
            
            //while loop to make sure proper value is entered
            while (!(cin >> num_input)) { // Loop until valid integer input
                cout << "Invalid input. Please enter an integer:\n";
                cin.clear(); // Clear the error state of cin
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n'); // Discard remaining invalid input
            }

            if(isValid(num_input)){
                int hash_number = hashFunction(num_input);
                bool isFound = searchLinkedList(num_input, table[hash_number]);

                if(isFound){
                    cout << "found it!\n";
                    cout << "hash key: " << hash_number << endl;
                    printLinkedList(table[hash_number]);
                    cout << endl;

                } else {
                    cout << "you stupid\n";
                }
            }else{
                cout << "invalid input. value must greater than " << MIN_VALUE << " and less than " << MAX_VALUE << endl;
            }
            

        }else if(input == 'c'){
            
            clearDuplicates(table);

        }else if (input == 'e'){
            cout << "exiting...\n";
            isRunning = false;
        }else if (input == 'p'){
            
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer

            string line;
            cout << "enter hash key to print. enter to print all:\n";

            getline(cin, line);

            if (line.empty()) {
                // User pressed enter - print all
                printMap(table);
            } else {
                // Try to parse as integer
                try {
                    int user_input = stoi(line);
                    if(isValidHash(user_input)){
                        cout << "hash key: " << user_input << endl;
                        printLinkedList(table[user_input]);
                        cout << endl;
                    } else {
                        cout << "invalid input. value must greater than " << hashFunction(MIN_VALUE) << " and less than " << hashFunction(MAX_VALUE) << endl;
                    }
                } catch (invalid_argument&) {
                    cout << "Invalid input. Please enter an integer:\n";
                }
            }
        }else {
            cout << "invalid command.\n";
        }

    }
}

int main() {

    int random_numbers[MAX_SIZE];//init the random value array
    hash_node* table[10] = {nullptr}; // 10 for 9 possible hash values - 0 is unused

    //init srand for random values
    srand((unsigned)time(0)); 

    //generates MAX_SIZE random ints and stores them in random_numbers
    generateRandomNumbers(random_numbers, MAX_SIZE);
    
    //maps numbers to the table using hash function.
    mapNumbers(random_numbers, MAX_SIZE, table);

    //print the un parsed table
    //printMap(table);

    //clear all duplicates in the table
    clearDuplicates(table);

    //output parsed table
    printMap(table);  
    
    //take user input and process
    userInput(table);
    
    return 0;
}