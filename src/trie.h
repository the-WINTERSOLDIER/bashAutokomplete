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
        void insert(const std::string&);
        std::vector<std::string> suggestions(const std::string&);
        void getallwords(const trienode* ,std::vector<std::string> &, const std::string&);
};
#endif
