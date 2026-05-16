#include <iostream>
#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Node
{
    int key;
    int height;
    Node *left = nullptr;
    Node *right = nullptr;
    Node(int key_input) : key(key_input) {};
};

void merge(int arr[], int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int *leftArr = new int[n1];
    int *rightArr = new int[n2];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back
    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {
        if (leftArr[i] <= rightArr[j])
        {
            arr[k] = leftArr[i];
            i++;
        }
        else
        {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of leftArr
    while (i < n1)
    {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy remaining elements of rightArr
    while (j < n2)
    {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    delete[] leftArr;
    delete[] rightArr;
}

void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
}

void buildTree(int arr[], Node *node, int size)
{
    if (size <= 0)
        return;

    int mid_index = size / 2;
    int left_size = mid_index;
    int right_size = size - mid_index - 1;
    node->key = arr[mid_index];

    (size != 0) ? node->height = floor(log2(size)) + 1 : node->height = 0;

    if (left_size > 0)
    {
        node->left = new Node(-1);
        int *left_half = new int[left_size];
        for (int i = 0; i < mid_index; i++)
        {
            left_half[i] = arr[i];
        }
        buildTree(left_half, node->left, left_size);
        delete[] left_half;
    }

    if (right_size > 0)
    {
        node->right = new Node(-1);
        int *right_half = new int[right_size];
        for (int i = 0; i < mid_index; i++)
        {
            right_half[i] = arr[i + mid_index + 1];
        }
        buildTree(right_half, node->right, right_size);
        delete[] right_half;
    }

    //cout << "key: " << node->key << " size: " << size << " height: " << node->height << "\n";
}

void kProbe(Node *node, int k, int &count, int &result)
{
    if (node == nullptr || count >= k)
        return;

    kProbe(node->left, k, count, result);

    count++;
    if (count == k)
    {
        result = node->key;
        return;
    }

    kProbe(node->right, k, count, result);
}

int findK(Node *root, int k)
{
    int count = 0;
    int result = -1;

    kProbe(root, k, count, result);

    return result;
}

vector<int> flattenTree(Node *node)
{

    vector<int> left = {};
    vector<int> right = {};

    if (node->left)
    {
        left = flattenTree(node->left);
    }

    if (node->right)
    {
        right = flattenTree(node->right);
    }

    vector<int> result = left;                               // Copy left vector
    result.push_back(node->key);                             // Add the node's key
    result.insert(result.end(), right.begin(), right.end()); // Add right vector
    return result;
}

void printTree(Node *root, int arr[], int arr_length)
{
    int width = arr_length;
    int max_height = root->height;

    int max_digits = to_string(*max_element(arr, arr + arr_length)).length();

    // int max_height = 7;
    // int width = pow(2, max_height) - 1;

    for (int i = 0; i < max_height; i++)
    { // i is current height
        for (int j = 0; j < pow(2, i); j++)
        {
            int spacing = j == 0 ? (2 * width / 2.0) * (1 / pow(2, i)) + (!(i == max_height - 1) ? 1 : 0) - 1 : (2 * width) * (1 / pow(2, i)) - max_digits + 1;

            int index = (int)(width / pow(2, i + 1)) + (int)((j)*pow(2, max_height - i));

            printf("%*s", (int)ceil(spacing), " ");

            cout << setw(max_digits) << arr[index];
        }
        printf("\n");

        for (int j = 0; j < pow(2, max_height - i - 1) - 1; j++)
        { // iterate down
            int branch_num = pow(2, i + 1);

            bool direction = false; // false is left, true is right
            for (int k = 0; k < branch_num; k++)
            { // iterate across

                int spacing = 0;

                switch (direction)
                {
                case false: // left
                    spacing = k == 0 ? (int)ceil(2 * width / 2.0) * (1 / pow(2, i)) + (!(i == max_height - 1) ? 1 : 0) - j - 4 + max_digits : (2 * width) * (1 / pow(2, i)) - 2 * j - 2;
                    printf("%*s", (int)ceil(spacing), " ");
                    printf("/");
                    direction = true;
                    break;
                case true: // right (inside)
                    spacing = j * 2 + 1;
                    printf("%*s", (int)ceil(spacing), " ");
                    printf("\\");
                    direction = false;
                    break;
                }
            }

            printf("\n");
        }
    }
}

int main()
{
    int input[] = {6, 17, 20, 41, 45, 52, 57, 65, 71, 76, 79, 87, 92, 95, 99};
    int arr_size = sizeof(input) / sizeof(input[0]);
    int k;

    mergeSort(input, 0, arr_size - 1);

    cout << "enter the value for k in determining the kth smallest element:\n";
    cin >> k;

    Node root = Node(-1);
    buildTree(input, &root, arr_size);

    int kth = findK(&root, k);

    cout << "kth: " << kth << "\n";

    printTree(&root, input, arr_size);

    return 0;
}