#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct TrieNode {
    TrieNode* children[26];
    int frequency;
    bool isTerminal;

    TrieNode() {
        for (int i = 0; i < 26; ++i) {
            children[i] = nullptr;
        }
        frequency = 0;
        isTerminal = false;
    }
};

class Trie {
public:
    TrieNode* root;

    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            int index = c - 'a';
            if (!curr->children[index]) {
                curr->children[index] = new TrieNode();
            }
            curr = curr->children[index];
            curr->frequency++;
        }
        curr->isTerminal = true;
    }

    string findSmallestUniquePrefix(const string& word) {
        TrieNode* curr = root;
        string prefix;
        for (char c : word) {
            int index = c - 'a';
            if (!curr->children[index]) {
                return prefix;
            }
            curr = curr->children[index];
            prefix += c;
            if (curr->frequency == 1 && curr->isTerminal) {
                return prefix;
            }
        }
        return "-1"; // If the entire word is a prefix of another, return "-1"
    }
};

int main() {
    vector<string> words = {"cobra", "cobras", "dog", "dove", "duck"};
    vector<string> output;

    Trie trie;
    for (const string& word : words) {
        trie.insert(word);
    }

    for (const string& word : words) {
        string prefix = trie.findSmallestUniquePrefix(word);
        output.push_back(prefix);
    }

    for (const string& prefix : output) {
        cout << prefix << " ";
    }
    cout << endl;

    return 0;
}