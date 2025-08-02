// Binary Search Tree (BST) implementation that loads, searches
// and delete a dataset from memory

// Has time complexity for insertion, searching and deletion of O(N)

#include "bst.h"

// Global variables
bstnode *root = NULL;

bool bst_insert(const char *data_file)
{
    // open data file
    FILE *inptr = fopen(data_file, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", data_file);
        return false;
    }

    // create a buffer
    int buffer;

    // Build list until reach the end of file
    while(fscanf(inptr, "%i", &buffer) != EOF)
    {
        bstnode *n = malloc(sizeof(bstnode));
        if (n == NULL)
        {
            bst_unload();
            return false;
        }

        n->number = buffer;
        n->left = NULL;
        n->right = NULL;

        // If list is empty
        if (root == NULL)
        {
            root = n;
        }

        else
        {
            bst_build(root, n);
        }
    }
    // Close the data file
    fclose(inptr);

    return true;
}


bool bst_search(int numbers)
{
    bstnode *n = root, *parent = NULL;
    while (n != NULL)
    {
        // if number is greater than current node
        if (numbers > n->number)
        {
            if (n->right != NULL)
            {
                parent = n;
                n = n->right;
            }
            else
            {
                return false;
            }
        }
        // if number is lesser than current node
        else if (numbers < n->number)
        {
            if (n->left != NULL)
            {
                parent = n;
                n = n->left;
            }
            else
            {
                return false;
            }
        }
        else
        {
            bst_delete(n, parent);
            return true;
        }
    }
    return false;
}

void bst_unload(void)
{
    bst_free(root);
}

// Deletes a node from the list
void bst_delete(bstnode *n, bstnode *parent)
{

    // edge case leaf node
    if (n->left == NULL && n->right == NULL)
    {
        // if it's the root node, just free it
        if (parent == NULL)
        {
            free(n);
            // reset root to NULL to avoid memory issue
            root = NULL;
            return;
        }
        else
        {
            if (parent->left == n)
            {
                parent->left = NULL;
            }
            else
            {
                parent->right = NULL;
            }
            free(n);
        }
    }

    // edge case only one child
    else if (n->left == NULL || n->right == NULL)
    {
        // Assigns n->left to child node if it's not null
        // otherwise, it assigns n->right
        bstnode *child = (n->left != NULL) ? n->left : n->right;

        // if the node is a root
        if (parent == NULL)
        {
            root = child;
        }

        // if node is not a root
        else
        {
            if (parent->left == n)
            {
                parent->left = child;
            }
            else
            {
                parent->right = child;
            }
        }

        free(n);
    }
    // node with two children
    else
    {
        bstnode *smallest = n->right;
        bstnode *prev = n;
        // find the successor - smallest node on the right subtree of N
        while (smallest->left != NULL)
        {
            prev = smallest;
            smallest = smallest->left;
        }

        // update N with the successor
        n->number = smallest->number;

        // if successor is deep in the tree
        if (prev != n)
        {
            prev->left = smallest->right;
        }
        // if successor is the immediate right child
        else
        {
            prev->right = smallest->right;
        }

        // free the successor node
        free(smallest);
    }
}

// Creates trees nodes
void bst_build(bstnode* current, bstnode* new)
{
    if (new->number < current->number)
    {
        if (current->left == NULL)
        {
            current->left = new;
            return;
        }
        bst_build(current->left, new);
    }

    else
    {
        if (current->right == NULL)
        {
            current->right = new;
            return;
        }
        bst_build(current->right, new);
    }
}

// Frees entire tree from memory
void bst_free(bstnode *n)
{
    if (n == NULL)
    {
        return;
    }
    bst_free(n->left);
    bst_free(n->right);
    free(n);
}

