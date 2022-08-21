#include<iostream>
#include"trie.h"
#include<fstream>
#include <vector>

int main(int argc, char *argv[]){
    std::string usage="hist <STR>\n hist command will parse through, that have STR as prefix.";
    // Validate cli args
    if (argc>2||argc<2){
        std::cout<<usage<<std::endl;
        exit(1);
    }

    trie word_list;
    std::fstream fo;
    fo.open("/home/anton/.bash_history",std::ios_base::in);
    std::string line;
    
    // Building Trie off of .bash_history
    while(getline(fo,line)){
         if(line[0]==' '){
             // skip if the first character of a command is space
            continue;
         }
         word_list.insert(line);
    }

    // Get prefix
    std::string prefix = argv[1]; 
    
    // Get list of all the suggestions
    std::vector<std::string> res= word_list.suggestions(prefix);
    
    // Print all the suggestions
    for (auto x: res){
        std::cout<<x<<std::endl;
    }
}
