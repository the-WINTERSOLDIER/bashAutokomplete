#include<iostream>
#include"trie.h"
#include<fstream>
#include <vector>
int main(){
    trie word_list;
    word_list.insert("hello");
    word_list.insert("help");
    word_list.insert("helmet");
    //std::vector<std::string> res=word_list.suggestions("hel");
    std::fstream fo;
    fo.open("/home/anton/.bash_history",std::ios_base::in);
    std::string line;
    while(getline(fo,line)){
         word_list.insert(line);
    }
    std::string prefix;
    std::cout<<"enter prefix"<<std::endl;
    std::cin>>prefix;
    
    std::vector<std::string> res= word_list.suggestions("git");
    for (auto x: res){
    std::cout<<x<<std::endl;
    }
}
