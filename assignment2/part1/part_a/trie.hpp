#ifndef TRIE
#define TRIE

#include <iostream>

class Trie {

    struct TrieNode {
        TrieNode* children[30];
        bool word_end = false;

        TrieNode(): word_end(false) {
            for(size_t i = 0; i < 30; ++i) {
                children[i] = nullptr;
            }
        }
    };
    
    TrieNode* root = nullptr;



public:
    
    Trie(): root(new TrieNode()) {}


    void insert(const std::string& word) {
        
        TrieNode* currNode = root; 
        for(auto symbol: word) {
            if(currNode->children[symbol - 'a'] == nullptr) {
                TrieNode* newNode = new TrieNode();
                currNode->children[symbol - 'a'] = newNode;
            }
            currNode = currNode->children[symbol - 'a'];
        }
        currNode->word_end = true;       
    }

    bool search(const std::string& word) {
        
        TrieNode* currNode = root;
        for(auto symbol: word) {
            if(currNode->children[symbol - 'a'] == nullptr) {
               return 0;
            }
            currNode = currNode->children[symbol - 'a'];
        }

        return currNode->word_end;
    }



};


#endif