#include <stdio.h>
#include "trie.h"

int main() {
    TrieNode * root = createNode();
    //insertLinesFromFile(root, "../words.txt");
    insert(root, "the");
    FILE *file = fopen("../trieSave.txt", "w");
    serializeTrie(root,file);
    root = deserializeTrie(file);
    //printf("%i\n", search(root,"faggot"));
    return 0;
}