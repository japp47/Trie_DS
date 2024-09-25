#include <bits/stdc++.h>
using namespace std;

class Node {
    public:
        int data;
        unordered_map<char, Node*> children;
        bool terminal;      //to store where it ends

        Node(char a) {
            data = a;
            terminal = false;
        }
};
class Trie {
    Node* root;
    int count;
    public:
        Trie() {
            root = new Node('\0');                  //starting--null character
            count = 0;
        }

    void insert(char* w) {
        Node* temp = root;
        for (int i = 0; w[i] != '\0'; i++) {
            char ch = w[i];
            if(temp->children.count(ch)) {
                temp = temp->children[ch];
            } else {
                Node* new_node = new Node(ch);
                temp->children[ch] = new_node;
                temp = new_node;
            }
        }
        temp->terminal = true;
    }

    bool find(char* w) {
        Node* temp = root;
        for (int i = 0; w[i] != '\0'; i++) {
            char ch = w[i];
            if(temp->children.count(ch)==0) {
                return false;
            } else {
                temp = temp->children[ch];
            }
        }
        return temp->terminal;
    }
};

int main() {
    Trie t;
    char words[][10] = {"a", "hello","no", "not", "news"};
    char w[10]; cin>>w;
    for (int i = 0; i < 5; i++) {
        t.insert(words[i]);
    }
    if(t.find(w)) {
        cout<<"word found"<<endl;
    } else{
        cout<<"Absent";
    }
    return 0;
}
