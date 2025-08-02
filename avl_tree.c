// AVL/ Height Balanced Tree implementation that loads, searches
// and delete a dataset from memory

// Has time complexity for insertion, searching and deletion of O(log N)

#include "avl_tree.h"

// Global variables
avlnode *avlroot = NULL;

// Function prototypes
int height(avlnode *n);
int max(int a, int b);
struct avlnode *avl_balance(avlnode *n);
struct avlnode *leftRotate(avlnode* n);
struct avlnode *rightRotate(avlnode* n);
struct avlnode *checkBalance(avlnode *n);
void updateHeight(avlnode *n);

// Insert a node in the AVL tree
bool avl_insert(const char *data_file)
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
        avlnode *n = malloc(sizeof(avlnode));
        if (n == NULL)
        {
            avl_unload();
            return false;
        }

        n->number = buffer;
        n->height = 0;
        n->left = NULL;
        n->right = NULL;

        avlroot = avl_build(avlroot, n);
    }
    // Close the data file
    fclose(inptr);

    return true;
}

// Search for a node in the AVL tree
bool avl_search(int numbers)
{
    avlnode *n = avlroot;
    while (n != NULL)
    {
        // if number is greater than current node
        if (numbers > n->number)
        {
            if (n->right != NULL)
            {
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
                n = n->left;
            }
            else
            {
                return false;
            }
        }
        else
        {
            avlroot = avl_delete(avlroot, numbers);
            return true;
        }
    }
    return false;
}

// Frees entire tree from memory
void avl_unload(void)
{
    avl_free(avlroot);
    avlroot = NULL;
}

// Deletes a node from the list
struct avlnode *avl_delete(avlnode *root, int number)
{
    // if value is to the left
    if (number < root->number)
    {
        // assign subroot recursively to the left value
        root->left = avl_delete(root->left, number);
    }
    // if value is to the right
    else if (number > root->number)
    {
            // assign subroot recursively to the right value
        root->right = avl_delete(root->right, number);
    }

    // if value is found
    else
    {
        // edge case leaf node
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }

        // edge case only one child
        else if (root->left == NULL || root->right == NULL)
        {
            // free the node and assign the child to the parent node
            avlnode *child = (root->left != NULL) ? root->left : root->right;
            free(root);
            return child;
        }
        // node with two children
        else
        {
            avlnode *smallest = root->right;
            avlnode *prev = root;
            // find the successor - smallest node on the right subtree of N
            while (smallest->left != NULL)
            {
                prev = smallest;
                smallest = smallest->left;
            }

            // update root with the successor
            root->number = smallest->number;

            // if successor is deep in the tree
            if (prev != root)
            {
                // reset the pointer of smallest's parent node
                prev->left = smallest->right;
            }
            // if successor is the immediate right child
            else
            {
                avlnode *temp = smallest->right;
                // reset the pointer of smallest's parent node
                root->right = temp;
            }

            // free the successor node
            free(smallest);
            return root;
        }
    }
    // update the height of the parent node
    updateHeight(root);

    // check if node is balanced
    return checkBalance(root);
}

// Creates trees nodes
struct avlnode *avl_build(avlnode* current, avlnode* new)
{
    // if list is empty
    if (current == NULL)
    {
        return new;
    }

    // if the number is smaller than the current node
    if (new->number < current->number)
    {
        // if the node to the left is available
        if (current->left == NULL)
        {
            current->left = new;

            // update the height of the parent node
            updateHeight(current);

            // Return unchanged node
            return current;

        }
        // recursively try to find an available node and assign it to the left child
        current->left = avl_build(current->left, new);
    }

    else if (new->number > current->number)
    {
        // if the node to the right is available
        if (current->right == NULL)
        {
            current->right = new;

            // update the height of the parent node
            updateHeight(current);

            // Return unchanged node
            return current;
        }
        // recursively try to find an available node and assign it to the right child
        current->right = avl_build(current->right, new);
    }
    // If the number already exists in the list, don't assign it to anything
    else
    {
        free(new);
        return current;
    }

    // update the height of the parent node
    updateHeight(current);

    // check if node is balanced
    return checkBalance(current);
}

// Frees entire tree from memory
void avl_free(avlnode *n)
{
    if (n == NULL)
    {
        return;
    }
    avl_free(n->left);
    avl_free(n->right);
    free(n);
}

// Return the height of a node
int height(avlnode *n)
{
    if (n == NULL)
    {
        return -1;
    }

    return n->height;
}

// Updates the height of a node
void updateHeight(avlnode *n)
{
    n->height = max(height(n->left), height(n->right)) + 1;
}

// Handles the left rotation of a node
struct avlnode *leftRotate(avlnode* n)
{
    avlnode *originalRoot = n;
    avlnode *temp = n->right->left;

    // right child assumes the root
    n = n->right;

    // original root is now the left child
    n->left = originalRoot;

    // adjust original root right child
    originalRoot->right = temp;

    // update the height of the rotated nodes
    updateHeight(originalRoot);
    updateHeight(n);

    return n;
}

// Handles the right rotation of a node
struct avlnode *rightRotate(avlnode* n)
{
    avlnode *originalRoot = n;
    avlnode *temp = n->left->right;

    // left child assumes the root
    n = n->left;

    // original root is now the right child
    n->right = originalRoot;

    // adjust original root left child
    originalRoot->left = temp;

    // update the height of the rotated nodes
    updateHeight(originalRoot);
    updateHeight(n);

    return n;
}

// Checks for balance in the AVL tree and return the updated node
struct avlnode *checkBalance(avlnode *n)
{
    // check for null node
    if (n == NULL)
    {
        return NULL;
    }
    // calculate the balance factor
    int balance = height(n->left) - height(n->right);

    // if the tree is left heavy
    if (balance > 1)
    {
        // compare the heights of the grandchildren
        if (height(n->left->left) >= height(n->left->right))
        {
            // Right Rotation
            return rightRotate(n);
        }
        else
        {
            // Left-Right Rotation
            n->left = leftRotate(n->left);
            return rightRotate(n);
        }

    }

    // if the tree is right heavy
    else if (balance < -1)
    {
        // compare the heights of the grandchildren
        if (height(n->right->right) >= height(n->right->left))
        {
            // Left Rotation
            return leftRotate(n);
        }
        else
        {
            // Left-Right Rotation
            n->right = rightRotate(n->right);
            return leftRotate(n);
        }
    }

    // if balanced, return the node
    return n;
}

// Gets the maximum between two numbers
int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}
