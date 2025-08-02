#ifndef DOUB_LINKEDLIST_H
#define DOUB_LINKEDLIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Represents a node in a linked list
typedef struct dllnode
{
    int number;
    struct dllnode *prev;
    struct dllnode *next;
} dllnode;

bool dll_insert(const char *data_file);
bool dll_search(int numbers);
void dll_unload(void);
void dll_delete(dllnode *n);

#endif
