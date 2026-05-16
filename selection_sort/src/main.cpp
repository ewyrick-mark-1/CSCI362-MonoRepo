#include <iostream>
#include <vector>

using namespace std;

void SelectionSort(vector<int>& arr, int size){
    
    for (int i = 0; i <size - 1; i++){
        int min_index = i;
        for(int j = i+1; j < size; j++){
            if(arr[j] < arr[min_index]){
                min_index = j;
            }
        }
        if(arr[min_index] < arr[i]){
            int temp = arr[i];
            arr[i] = arr[min_index];
            arr[min_index] = temp;
        }
        
    }
}

int main() {
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    // Create a vector of the specified size
    vector<int> arr(size); 

    cout << "Enter integers:\n";

    for (int i = 0; i < size; ++i) { // for loop for taking a vector input
        cout << "Enter element " << i + 1 << ": ";
        cin >> arr[i];
    }

    cout << "Array elements are: ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";

        
    }
    cout << "\n";
    SelectionSort(arr, size);
    cout << "sorted array elements are: ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";

        
    }


    return 0;
}