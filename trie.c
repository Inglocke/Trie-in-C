#include "trie.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


TrieNode *createNode(void){
    TrieNode * retNode = malloc(sizeof(TrieNode));
    for(int i = 0; i < 256; i++){
        retNode->children[i] = NULL;
    }
    retNode->is_end_of_word = false;
    return retNode;
}

// Function to insert a word into the Trie

void insert(TrieNode *root, const char *word){
    TrieNode * curNode = root;
    for (int i = 0; i < strlen(word); ++i) {
        if(curNode->children[word[i]] == NULL){
            curNode->children[word[i]] = createNode();
        }
        curNode = curNode->children[word[i]];
    }
    curNode->is_end_of_word = true;
}



// Function to search for a word in the Trie

bool search(TrieNode *root, const char *word){
    return getLastNodeInWord(root, word)->is_end_of_word;
}



// Function to check if a node has children

bool isLeafNode(TrieNode *node){
    for (int i = 0; i < 256; ++i) {
        if(node->children[i] != NULL){
            return false;
        }
    }
    return true;
}


TrieNode * getLastNodeInWord(TrieNode * root, const char *word){
    TrieNode * curNode = root;
    for (int i = 0; i < strlen(word); ++i) {
        if(curNode->children[word[i]] == NULL){
            return false;
        }
        curNode = curNode->children[word[i]];
    }
    return  curNode;
}

// Function to delete a word from the Trie
//TO DO
bool delete(TrieNode **root, char *word){
    if(!search(*root, word))
        return false;
    TrieNode * curNode = *root;
    for (int i = strlen(word); i > 0; --i) {
        word[i] = '\0';
        getLastNodeInWord(*root, word);
    }
}



// Optional: Function to display the content of the Trie

void display(TrieNode *root, char str[], int level);


void insertLinesFromFile(TrieNode *root, const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filePath);
        return;
    }

    char line[256];  // Assuming a maximum line length of 255 characters
    while (fgets(line, sizeof(line), file)) {
        // Remove newline character if present
        if (line[strlen(line) - 1] == '\n') {
            line[strlen(line) - 1] = '\0';
        }
        insert(root, line);
    }

    fclose(file);
}

void serializeTrie(FILE* file, TrieNode* node) {
    if (node == NULL) {
        fwrite("#", sizeof(char), 1, file);
        return;
    }

    fwrite("N", sizeof(char), 1, file);

    for (int i = 0; i < 256; i++) {
        serializeTrie(file, node->children[i]);
    }
}

TrieNode* deserializeTrie(FILE* file) {
    char marker;
    fread(&marker, sizeof(char), 1, file);

    if (marker == '#') {
        // NULL node marker
        return NULL;
    } else if (marker == 'N') {
        // Valid node marker

        // Create a new trie node
        TrieNode* newNode = createNode();

        // Read node data (if any)
        // Example: fread(&(newNode->someData), sizeof(int), 1, file);

        // Recursively deserialize child nodes
        for (int i = 0; i < 256; i++) {
            newNode->children[i] = deserializeTrie(file);
        }

        return newNode;
    } else {
        // Handle unrecognized marker (error case)
        fprintf(stderr, "Error: Unrecognized marker '%c'\n", marker);
        return NULL;
    }
}
