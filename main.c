#include <stdio.h>
#include "trie.h"

int main() {
    TrieNode * root;
    //insertLinesFromFile(root, "../words.txt");
    insert(root, "the");
    FILE *file = fopen("../trieSave.txt", "r");
   // serializeTrie(file,root);
    root = deserializeTrie(file);
    printf("%i\n", search(root,"the"));
    return 0;
}