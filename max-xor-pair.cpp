#include<bits/stdc++.h>
using namespace std;

class Node {
    public:
        Node* left;
        Node* right;
};
class trie {
    Node* root;
    public:
        trie() {
            root = new Node();
        }
        void insert(int n) { 
            Node* temp = root;
            for(int i = 31;i>=0;i--){  //32 bit integer
                int bit = (n>>i)&1;       //MSB
                if(bit == 0) {
                    if(temp->left == NULL) {
                        temp->left = new Node();
                    }
                    temp = temp->left;
                } else{
                    if(temp->right == NULL) {
                        temp->right = new Node();
                    }
                    temp = temp->right;
                }
            }   
        }
        int max_xor_helper(int num) {
            int curr = 0;
            Node* temp = root;
            int best_match = 0;  // Track the number with max XOR

            for(int i = 31;i>=0;i--) {
                int bit = (num>>i)&1;  //extracitng bit
                if(bit==0) {
                    if(temp->right != NULL) {
                        temp = temp->right;
                        curr = curr + (1<<i);
                       // best_match |= (1 << i);  // Set the bit in the best match

                    } else{
                        temp = temp->left;
                    }
                } else {
                    //current bit is 1
                    if(temp->left != NULL) {
                        temp = temp->left;
                        curr = curr + (1<<i);
                       // best_match |= (1 << i);  // Set the bit in the best match

                    } else{
                        temp = temp->right;
                    }
                }
            }
            return curr;
        }

        //to get the pair use this

        //  pair<int, int> max_xor(int* input, int n) {
        //     int maxXor = 0;
        //     int num1 = 0, num2 = 0;
            
        //     insert(input[0]);  // Insert the first number
            
        //     for(int i = 1; i < n; i++) {
        //         int curr_num = input[i];
        //         int best_match = 0;  // Store the number that produces max XOR with curr_num
        //         int curr_xor = max_xor_helper(curr_num, best_match);
        //         if(curr_xor > maxXor) {
        //             maxXor = curr_xor;
        //             num1 = curr_num;
        //             num2 = best_match;  // The number in the trie that gives max XOR
        //         }
        //         insert(curr_num);  // Insert current number into trie
        //     }
            
        //     return {num1, num2};  // Return the pair that gives max XOR
        // }
        int max_xor(int* input, int n) {
            int maxXor = 0;
            for(int i = 0;i<n;i++) {
                int num = input[i];
                insert(num);
                int curr_xor = max_xor_helper(num);
                //cout<<curr_xor<<" ";
                maxXor = max(maxXor, curr_xor); 
            }
            return maxXor;
        }
};
int main() {
    int input[] = {3,10,5,25,2,8};
    int n = sizeof(input)/sizeof(input[0]);
    trie t;
    // pair<int, int> result = t.max_xor(input, n);

    int maxXor = t.max_xor(input, n);
    cout<<maxXor;
    return 0;
}