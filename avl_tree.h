#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct avlnode
{
    int number;
    int height;
    struct avlnode *left;
    struct avlnode *right;
} avlnode;

bool avl_insert(const char *data_file);
bool avl_search(int numbers);
void avl_unload(void);
struct avlnode *avl_delete(avlnode *root, int number);
struct avlnode *avl_build(avlnode* current, avlnode* new);
void avl_free(avlnode *n);

#endif
