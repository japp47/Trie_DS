// Given an m x n board of characters and a list of strings words, return all words on the board.

// Each word must be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.

#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int m, n;
    vector<string> res;
    vector<pair<int, int>> dir = {{-1,0},{0,-1},{1,0},{0,1}};
    
    struct node {
        bool terminal;
        node* children[26];
        string word;
    };
    
    node* getNode() {
        node* newNode = new node();
        newNode->terminal = false;
        for(int i = 0; i < 26; i++) {
            newNode->children[i] = NULL;
        }
        newNode->word = "";
        return newNode;
    }

    void insert(node* root, string str) {
        node* temp = root;
        for(char ch: str) {
            int idx = ch - 'a';
            if(!temp->children[idx]) {
                temp->children[idx] = getNode();
            }
            temp = temp->children[idx];
        }
        temp->terminal = true;
        temp->word = str;
    }

    void dfs(vector<vector<char>>& board, int i, int j, node* root) {
        if(i < 0 || j < 0 || i >= m || j >= n || board[i][j] == '#' || !root->children[board[i][j] - 'a']) return;

        root = root->children[board[i][j] - 'a'];
        if(root->terminal == true) {
            res.push_back(root->word);
            root->terminal = false;
        }

        char temp = board[i][j];
        board[i][j] = '#';

        for(pair<int, int> d: dir) {
            int _i = i + d.first;
            int _j = j + d.second;
            dfs(board, _i, _j, root);
        }
        board[i][j] = temp;
    }

    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        m = board.size();
        n = board[0].size();
        node* root = getNode();
        for(string word: words) {
            insert(root, word);
        }

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                char ch = board[i][j];

                if(root->children[ch - 'a'] != NULL) {
                    dfs(board, i, j, root);
                }
            }
        }
        return res;
    }
};

int main() {
    Solution solution;

    vector<vector<char>> board = {
        {'o', 'a', 'a', 'n'},
        {'e', 't', 'a', 'e'},
        {'i', 'h', 'k', 'r'},
        {'i', 'f', 'l', 'v'}
    };

    vector<string> words = {"oath", "pea", "eat", "rain"};

    vector<string> foundWords = solution.findWords(board, words);

    for(const string& word : foundWords) {
        cout << word << " ";
    }
    cout << endl;

    return 0;
}
