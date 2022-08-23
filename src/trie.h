#ifndef TRIE_H
#define TRIE_H
#include<map>
#include<string>
#include<vector>

class trienode {
    public:
        bool end_of_word;
        std::map<char,trienode*> children;
};

class trie{
    private:
        trienode root;
    public:
        void insert(const std::string);
        std::vector<std::string> suggestions(std::string);
        void getallwords(trienode* ,std::vector<std::string> &res, std::string);
};
#endif
