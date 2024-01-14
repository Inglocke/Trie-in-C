cmake_minimum_required(VERSION 3.26)
project(Trie C)

set(CMAKE_C_STANDARD 11)

add_executable(Trie main.c
        trie.h
        trie.c)
