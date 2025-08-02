#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Represents a node in a trie
typedef struct trienode
{
    bool end;
    struct trienode *number[10];
} trienode;

typedef struct listnode
{
    int digit;
    struct listnode *next;
} listnode;

bool trie_insert(const char *data_file);
bool trie_search(int numbers);
void trie_unload(void);

#endif
