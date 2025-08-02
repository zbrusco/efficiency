#ifndef HASHING_H
#define HASHING_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Represents a node in a hash table
typedef struct hashnode
{
    int number;
    struct hashnode *next;
} hashnode;

bool hash_insert(const char *data_file);
bool hash_search(int numbers);
void hash_unload(void);

#endif
