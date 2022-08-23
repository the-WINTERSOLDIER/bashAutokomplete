#include"trie.h"
#include<iostream>

void trie::insert(const std::string word){
    trienode *temp = &(this->root);
    for( char letter : word){
        if(temp->children[letter] == NULL){
                temp->children[letter]= new trienode;
            }
            temp = temp->children[letter];
        }
        temp->end_of_word = true;
}

void trie::getallwords(trienode *root,std::vector<std::string>& res, std::string word){
    if(root->end_of_word==true||root->children.size()==0){
        res.push_back(word);
    }

    for (auto it : root->children){
        getallwords(it.second,res,word+(it.first));
   }  
}

std::vector<std::string> trie::suggestions(std::string word){
    std::vector<std::string> res;
    trienode *temp = &(this->root);
    // Get root node after prefix word
    if(! word.empty()){
    for (char letter : word){
        if(temp->children[letter] != NULL){
            temp=temp->children[letter];
        }
    }
    }
    this->getallwords(temp,res,word);
    return res;
}
