#ifndef BST_H
#define BST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct bstnode
{
    int number;
    struct bstnode *left;
    struct bstnode *right;
} bstnode;

bool bst_insert(const char *data_file);
bool bst_search(int numbers);
void bst_unload(void);
void bst_delete(bstnode *n, bstnode *parent);
void bst_build(bstnode* current, bstnode* new);
void bst_free(bstnode *n);

#endif
