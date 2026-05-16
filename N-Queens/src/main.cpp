#include <iostream>
#include <cmath>
#include <vector>
#include <stack>
#include <array>

using namespace std;

int SIZE = 0;

bool isValid(int row, int col, stack<array<int, 2>> stk){
    while(!stk.empty()){
        int qRow = stk.top()[0];
        int qCol = stk.top()[1];
        stk.pop();
        if(qCol == -1) continue; // skip dummy entries
        if(row == qRow || col == qCol || abs(row - qRow) == abs(col - qCol)){
            return false;
        }
    }
    return true;
}

int main(){
    cout << "enter number of queens (an integer between 4 and 10):\n";
    cin >> SIZE;
    while(SIZE < 4 || SIZE > 10){
        cout << "Invalid input. Please enter a number between 4 and 10:\n";
        cin >> SIZE;
    }

    stack <array<int, 2>> queenStack; // [row, col], [row, col]
    queenStack.push({0, -1});
    int solution_counter = 0;

    while(!queenStack.empty()){
        int row = queenStack.top()[0];
        int col = queenStack.top()[1];
        queenStack.pop();

        if(row == SIZE){
            //yay
            solution_counter++;
            cout << "solution " <<solution_counter<< " found\n";
            stack<array<int,2>> temp = queenStack;  // copy
            vector<array<int,2>> solution;
            while(!temp.empty()){
                solution.push_back(temp.top());
                temp.pop();
            }
            for(int r = solution.size()-1; r >= 0; r--){
                for(int n = 0; n < SIZE; n++){
                    if(n == solution[r][1]){
                        cout << " Q";
                    }else{
                        cout <<" .";
                    }
                }
                cout << '\n';
            }
            cout << '\n';
            continue;
        }

        for(int i = col+1; i < SIZE; i++){
            if(isValid(row, i, queenStack)){
                queenStack.push({row, i}); // push current valid column
                queenStack.push({row + 1, -1}); // push next row
                break;
            }
        }
    }
    
    return 0;
}
