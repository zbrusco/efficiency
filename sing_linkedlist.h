#ifndef SING_LINKEDLIST_H
#define SING_LINKEDLIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Represents a node in a linked list
typedef struct node
{
    int number;
    struct node *next;
} node;

bool sll_insert(const char *data_file);
bool sll_search(int numbers);
void sll_unload(void);
void sll_delete(node *n, node *prev);

#endif
