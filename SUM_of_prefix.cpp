// You are given an array words of size n consisting of non-empty strings.

// We define the score of a string word as the number of strings words[i] such that word is a prefix of words[i].

// For example, if words = ["a", "ab", "abc", "cab"], then the score of "ab" is 2, since "ab" is a prefix of both "ab" and "abc".
// Return an array answer of size n where answer[i] is the sum of scores of every non-empty prefix of words[i].

// Note that a string is considered as a prefix of itself.


#include <bits/stdc++.h>
using namespace std;

struct Node {
    Node* children[26];
    int countP;
};

class Solution {
public:
    Node* getNode() {
        Node* newNode = new Node();
        for (int i = 0; i < 26; i++) {
            newNode->children[i] = nullptr;
        }
        newNode->countP = 0;
        return newNode;
    }

    void insert(string& word, Node* root) {
        Node* temp = root;
        for (int i = 0; i < word.length(); i++) {
            int idx = word[i] - 'a';
            if (temp->children[idx] == nullptr) {
                temp->children[idx] = getNode();
            }
            temp->children[idx]->countP += 1;
            temp = temp->children[idx];
        }
    }

    int getScore(string& word, Node* root) {
        Node* temp = root;
        int score = 0;
        int n = word.size();
        for (int i = 0; i < n; i++) {
            int idx = word[i] - 'a';
            score += temp->children[idx]->countP;
            temp = temp->children[idx];
        }
        return score;
    }

    vector<int> sumPrefixScores(vector<string>& words) {
        int n = words.size();
        Node* root = getNode();
        for (string& word : words) {
            insert(word, root);
        }
        vector<int> res(n);
        for (int i = 0; i < n; i++) {
            res[i] = getScore(words[i], root);
        }
        return res;
    }
};

int main() {
    Solution solution;
    vector<string> words = {"abc", "ab", "bc", "b"};
    vector<int> result = solution.sumPrefixScores(words);

    cout << "Prefix scores for the given words:\n";
    for (int score : result) {
        cout << score << " ";
    }
    cout << endl;

    return 0;
}
