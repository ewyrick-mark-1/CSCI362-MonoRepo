
#include <iostream> // For output to console (e.g., printing file content)
#include <fstream>  // For file stream operations (ifstream, ofstream, fstream)
#include <string>   // For using std::string to store lines or words
#include <cmath>
#include <vector>
#include <algorithm>

#include "keyboard.hh"

using namespace std;

//init the struct array with the correct number of values
keyboard_coords table[36];

//custom hash table: 26*26 = 676 buckets based on first two letters
vector<string> hashTable[676];

float EX_CHAR_MODIFIER = 1.5; // modifier the penalizes extra characters. 
float MISSPELLING_THRESHOLD = INFINITY;

bool isAlpha(char c){
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int hashFunction(const string& word){
    if(word.length() == 0) return 0;

    if(!isAlpha(word[0])) return 0; //basic check - was getting seg faults

    if(word.length() == 1) return toupper(word[0]) - 'A';

    int first = toupper(word[0]) - 'A';

    int secondIdx = 1;
    while(secondIdx < word.length() && !isAlpha(word[secondIdx])){
        secondIdx++;
    }

    if(secondIdx >= word.length()) return first;

    int second = toupper(word[secondIdx]) - 'A';
    return first * 26 + second; // hash function returns [1-26] * 26 + [1-26], based on the first two values

}

vector<int> vectorize(string input){

    vector<int> vectored_input = {}; //init the return value

    if(sizeof(input) > 0){
        for(int i = 0; i < input.length(); i++){
            if(isAlpha(input[i])){
                vectored_input.push_back((int)toupper(input[i]) - (int)'A');
            }
        }
    }

    return vectored_input;
}

float calculateKeyboardDistance(int a, int b){
    return sqrt(pow((table[a].x - table[b].x), 2) + pow((table[a].y - table[b].y), 2));
}

float calculateDistance(string user_input, string to_compare){
    vector<int> user_vector = vectorize(user_input);
    vector<int> compare_vector = vectorize(to_compare);

    int max_len = max(user_input.length(), to_compare.length());

    //calculate the distance between vectors
    float distance = 0.0;
    for(int i = 0; i < max_len; i++){
        if(i < user_vector.size() && i < compare_vector.size() ){
            distance += calculateKeyboardDistance(user_vector[i], compare_vector[i]);
        }else if(i < user_vector.size()){
            distance += EX_CHAR_MODIFIER;
        }else if(i < compare_vector.size()){
            distance += EX_CHAR_MODIFIER;
        }
    }
    return distance;
}

void loadTable(const string& filename){
    ifstream inputFile(filename);
    //basic check for if file can be read from
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        exit(1);
    }

    string word;
    while (inputFile >> word){
        int index = hashFunction(word);
        //hash each value
        hashTable[index].push_back(word);
    }
    inputFile.close();
}

bool wordExists(const string& word){
    int index = hashFunction(word);
    //iterate & check
    for(const auto& w : hashTable[index]){
        if(w == word) return true;
    }
    return false;
}

vector<string> getSuggestions(const string& word){
    if(word.length() < 2) return {};

    int index = hashFunction(word);
    vector<pair<float, string>> distancePairs;

    for(const auto& dictWord : hashTable[index]){
        float dist = calculateDistance(word, dictWord);
        distancePairs.push_back({dist, dictWord});
    }

    sort(distancePairs.begin(), distancePairs.end());

    vector<string> result;
    int count = 0;
    for(const auto& pair : distancePairs){
        if(count >= 5) break;
        result.push_back(pair.second);
        count++;
    }

    return result;
}

string findClosestWord(const string& input, const string& firstLetter){
    string closest_word = "";
    float min_distance = 1000000.0;

    for(int i = 0; i < 676; i++){
        for(const auto& word : hashTable[i]){
            if(word.length() > 0 && toupper(word[0]) == toupper(firstLetter[0])){
                float distance = calculateDistance(input, word);
                if(distance < min_distance){
                    min_distance = distance;
                    closest_word = word;
                }
            }
        }
    }

    if(min_distance < MISSPELLING_THRESHOLD){
        return closest_word;
    }
    return "";
}

void handleCase1(const string& word){
    //passes all conditions
    cout << "True" << endl;
    vector<string> suggestions = getSuggestions(word);
    if(!suggestions.empty()){
        cout << "Words starting with the same first two letters (top 5):" << endl;
        int count = 0;
        for(const auto& suggestion : suggestions){
            if(count >= 5) break;
            cout << "  " << suggestion << endl;
            count++;
        }
    }
}

void handleCase2(const string& input){
    //case2 -> case1
    //handles case where input does not match a word in the dict
    string closest = findClosestWord(input, input.substr(0, 1));

    if(!closest.empty()){
        cout << "Do you mean " << closest << "? (yes/no): ";
        string response;
        cin >> response;

        if(response == "yes" || response == "y"){
            handleCase1(closest); //correct prediction
        } else {
            cout << "False" << endl;
        }
    } else {
        cout << "False" << endl;
    }
}

int main(int argc, char* argv[]) {
    if(argc < 2){
        cerr << "Usage: " << argv[0] << " <dictionary_file>" << endl;
        return 1;
    }

    //init the keyboard values
    initKeyboard(table);

    loadTable(argv[1]);

    string input;
    while(true){ //simple control loop
        cout << "\nEnter a word (or 'quit' to exit): ";
        cin >> input;

        if(input == "quit" || input == "exit"){
            break;
        }

        if(input.length() == 0){
            cout << "False" << endl;
            continue;
        }

        if(input.length() == 1){
            if(wordExists(input)){
                cout << "True" << endl;
            } else {
                cout << "False" << endl;
            }
            continue;
        }

        if(wordExists(input)){
            handleCase1(input);
        } else {
            handleCase2(input);
        }
    }

    return 0;
}
