// Author: Nishant Sharma
// Created: 2026-03-31 22:05:12
#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

struct Node{
    Node* links[26];
    bool flag = false;

    Node(){
        for(int i = 0; i < 26; ++i){
            links[i] = nullptr;
        }
    }

    bool containsKey(char ch){
        return links[ch - 'a'] != nullptr;
    }

    void put(char ch, Node* node){
        links[ch - 'a'] = node;
    }

    Node* get(char ch){
        return links[ch - 'a']; 
    }

    void setEnd(){
        flag = true;
    }

    bool isEnd(){
        return flag;
    }
}

class Trie{
    private:
        Node* root;

    public:
        Trie(){
            root = new Node();
        }

        void insert(string word){
            Node* node = root;
            for(int i = 0;  i < word.size(); ++i){
                if(!node->containsKey(word[i])){
                    node->put(word[i], new Node());
                }
                node = node->get(word[i]);
            } 
            node->setEnd();
        }

        bool search(string word){
            Node* node = root;
            for(int i = 0; i < word.size(); ++i){
                if(!node->containsKey(word[i])) return false;
                node = node->get(word[i]);
            }
            return node->isEnd();
        }
        
        bool startsWith(string prefix){
            Node* node = root;
            for(int i = 0; i < prefix.size(); ++i){
                if(!node->containsKey(prefix[i])) return false;
                node = node->get(prefix[i]);
            }
            return true; 
        }

};


int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

}