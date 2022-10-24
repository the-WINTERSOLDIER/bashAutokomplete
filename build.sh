g++ ./src/main.cpp -o ./src/main.o -c
g++ ./src/trie.cpp -o ./src/trie.o -c
g++ -o bashAutokomplete ./src/main.o ./src/trie.o -lncurses 
rm -rf ./src/*.o
