g++ main.cpp -o main.o -c
g++ trie.cpp -o trie.o -c
g++ -o bashAutokomplete main.o trie.o 
rm -rf *.o
