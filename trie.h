//
// Created by gusta on 12.01.2024.
//

#ifndef TRIE_TRIE_H
#define TRIE_TRIE_H

#include <stdbool.h>
#include <stdio.h>



// Define the Trie Node Structure

typedef struct trie_node {

    struct trie_node *children[256]; // Assuming the Trie is for the 26 English letters

    bool is_end_of_word;

} TrieNode;



// Function to create a new Trie node

TrieNode *createNode(void);


// Function to insert a word into the Trie

void insert(TrieNode *root, const char *word);



// Function to search for a word in the Trie

bool search(TrieNode *root, const char *word);



// Function to check if a node has children

bool isLeafNode(TrieNode *node);



// Function to delete a word from the Trie

bool delete(TrieNode **root, char *word);



// Optional: Function to display the content of the Trie

void display(TrieNode *root, char str[], int level);

void insertLinesFromFile(TrieNode *root, const char *filePath);

TrieNode * getLastNodeInWord(TrieNode * root, const char *word);

void serializeTrie(TrieNode* root, FILE* file);

TrieNode* deserializeTrie(FILE* file);

#endif //TRIE_TRIE_H

