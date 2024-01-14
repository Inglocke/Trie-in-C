#include "trie.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#define NULL_MARKER ((TrieNode*)1)

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
    TrieNode * lastNode = getLastNodeInWord(root, word);
    if(lastNode == NULL)
        return false;
    return lastNode->is_end_of_word;
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
            return NULL;
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

void serializeTrie(TrieNode* root, FILE* file) {
    if (root == NULL) {
        // Write a marker to indicate that the node is NULL
        fwrite(NULL_MARKER, sizeof(TrieNode), 1, file);
        return;
    }

    fwrite(root, sizeof(TrieNode), 1, file);

    for (int i = 0; i < 256; ++i) {
        serializeTrie(root->children[i], file);
    }
}

TrieNode* deserializeTrie(FILE* file) {
    TrieNode* root = malloc(sizeof(TrieNode));
    fread(root, sizeof(TrieNode), 1, file);

    // Check for the NULL marker
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Waddress"
    if (root == NULL_MARKER) {
        free(root);  // Free the memory allocated for the marker
        return NULL;
    }
#pragma GCC diagnostic pop


    for (int i = 0; i < 256; ++i) {
        root->children[i] = deserializeTrie(file);
    }

    return root;
}