// Problem Name: Range Xor
// Problem Difficulty: 2
// Problem Constraints: 0 <= element of array <= 10^9 <br>
// 1 <= N <= 10^5
// Problem Description:
// You are given an array and Q queries of two types.<br>
// Type 0: Given a number x , insert the number at the last of the array.<br>
// Type 1: Given a number X and two integers L, R, Find a number Y in the range L, R to maximize X ^ Y

// Input Format: 
// First line of the test case will be the number of queries Q .
// Then on next Q subsequent lines you will be given a query either of type 0 or type 1. Query of type 0 is of the form : 0 X, where X is the integer to be inserted .
// Query of type 1 is of the form : 1 L R X
// Sample Input: 5
// 0 3 
// 0 5
// 0 10 
// 0 6 
// 1 1 4 6
// Output Format: For each query of type 1 output the desired value.
// Sample Output: 10

#include <bits/stdc++.h>

using namespace std;

class TrieNode {
public:
    TrieNode* left;
    TrieNode* right;
    vector<int> indexes;

    TrieNode() {
        left = nullptr;
        right = nullptr;
    }
};

void insert(int n, TrieNode* head, int idx) {
    TrieNode* curr = head;
    for (int i = 31; i >= 0; i--) {
        int bit = (n >> i) & 1;
        if (bit == 0) {
            if (curr->left == nullptr) {
                curr->left = new TrieNode();
            }
            curr->indexes.push_back(idx);
            curr = curr->left;
        } else {
            if (curr->right == nullptr) {
                curr->right = new TrieNode();
            }
            curr->indexes.push_back(idx);
            curr = curr->right;
        }
    }
    curr->indexes.push_back(idx);
}

bool binarySearchRange(const vector<int>& arr, int l, int r) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int val = arr[mid];
        if (val >= l && val <= r) {
            return true;
        } else if (val < l) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}
int maxXor(int value, TrieNode* head, int left, int right) {
    int curr_xor = 0;
    TrieNode* curr = head;
    for (int j = 31; j >= 0; j--) {
        int b = (value >> j) & 1;
        if (b == 0) {
            if (curr->right != nullptr && binarySearchRange(curr->right->indexes, left, right)) {
                curr = curr->right;
                curr_xor += static_cast<int>(pow(2, j));
            } else {
                curr = curr->left;
            }
        } else {
            if (curr->left != nullptr && binarySearchRange(curr->left->indexes, left, right)) {
                curr = curr->left;
            } else {
                curr = curr->right;
                curr_xor += static_cast<int>(pow(2, j));
            }
        }
    }
    return curr_xor;
}


int main() {
    int q;
    cin >> q;
    TrieNode* head = new TrieNode();
    int elementNumber = 0;
    
    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        
        if (type == 0) {
            int val;
            cin >> val;
            insert(val, head, elementNumber++);
        } else if (type == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            cout << maxXor(x, head, l - 1, r - 1) << endl;
        }
    }

    return 0;
}
