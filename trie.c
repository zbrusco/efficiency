// Trie implementation that loads numbers, searches
// and deletes a dataset from memory

// Has time complexity for insertion, searching and deletion of O(m)
// with m being the lenght of the number being inserted


#include "trie.h"

// Function prototypes
void list_build(int digit);
struct trienode *trie_delete(trienode* root, listnode* head);
struct trienode* trie_free(trienode* root);
void list_free(void);

// Global Variables
listnode *listhead = NULL;
trienode *trieroot = NULL;

bool trie_insert(const char *data_file)
{
    // open data file
    FILE *inptr = fopen(data_file, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", data_file);
        return false;
    }

    trieroot = calloc(1, sizeof(trienode));
    if (trieroot == NULL)
    {
        fclose(inptr);
        return false;
    }

    // create a buffer
    int buffer;

    // Build list until reach the end of file
    while(fscanf(inptr, "%i", &buffer) != EOF)
    {
        // store each digit in a linked list
        list_build(buffer);

        listnode *cursor = listhead;
        trienode *n = trieroot;

        // load the list to the trie array
        while (listhead != NULL)
        {
            trienode *next = NULL;
            // if node doesn't exist for that number, create it
            if (n->number[cursor->digit] == NULL)
            {
                next = calloc(1, sizeof(trienode));
                if (next == NULL)
                {
                    trie_unload();
                    fclose(inptr);
                    return false;
                }

                // assign the new address to the digit
                n->number[cursor->digit] = next;
                // move n to the next value of the trie
                n = next;
            }

            // if node already exists
            else
            {
                // assign n to the address for that digit
                n = n->number[cursor->digit];
            }

            // if node is at the end of the list
            if (cursor->next == NULL)
            {
                // set the end of number flag to true
                n->end = true;
                break;
            }

            // move down the linked list
            cursor = cursor->next;
        }
    }

    // Close the data file
    fclose(inptr);
    return true;
}

bool trie_search(int numbers)
{
    // store each digit in a linked list
    list_build(numbers);
    trienode *n = trieroot;
    listnode *current = listhead;

    // while not at the end of the list
    while (current != NULL)
    {
        // end of the linked list
        if (current->next == NULL)
        {
            // check if that digit has an address
            if (n->number[current->digit] != NULL)
            {
                n = n->number[current->digit];
                // if that addresse's flag represents the end of a number
                if (n->end == true)
                {
                    // reset the cursor
                    current = listhead;
                    // delete the number from the TRIE
                    trieroot = trie_delete(trieroot, current);
                    return true;
                }
                else
                {
                    list_free();
                    return false;
                }
            }
            else
            {
                list_free();
                return false;
            }
        }
        // if not at the end of list, but the pointer exists
        else if (n->number[current->digit] != NULL)
        {
            // set n to the new pointer
            n = n->number[current->digit];
            // move to the next value on the list
            current = current->next;
        }
        // if not at the end and the pointer doesn't exist
        else
        {
            list_free();
            // return number not found
            return false;
        }
    }
    list_free();
    return false;
}

// Call the function to unload the trie from memory
void trie_unload(void)
{
    trieroot = trie_free(trieroot);

    // free the linked list
    list_free();
}

// Frees the entire Trie from memory
struct trienode* trie_free(trienode* root)
{
        // recursively check each children
        for (int i = 0; i <= 9; i++)
        {
            if (root->number[i] != NULL)
            {
                root->number[i] = trie_free(root->number[i]);
            }
        }

        // all children from that adress are null
        // then free it from memory
        free(root);

        return NULL;
}

// Create a prepending linked list with the digits of the number freeing the previous one from memory
void list_build(int number)
{
    // Frees previous list allocation
    list_free();
    // store each digit in a linked list
    while (number > 0)
    {
        int digit = number % 10;
        // create a linked list with prepending digits
        listnode *n = malloc(sizeof(listnode));
        if (n == NULL)
        {
            list_free();
            return;
        }
        n->digit = digit;
        n->next = NULL;

        // if list is empty
        if (listhead == NULL)
        {
            listhead = n;
        }
        else
        {
            n->next = listhead;
            listhead = n;
        }
        number /= 10;
    }
    return;
}

// Free the list from memory
void list_free(void)
{
    // If a list exists, clear it
    while (listhead != NULL)
    {
        listnode *temp = listhead->next;
        free(listhead);
        listhead = temp;
    }
    // set listhead back to null
    listhead = NULL;
}

// Delete a number from the trie
struct trienode *trie_delete(trienode* root, listnode* head)
{
    // if at the end of the digit list
    if (head->next == NULL)
    {
        trienode* child = root->number[head->digit];
        // set the end flag to false
        child->end = false;

        // Check if the child has children
        for (int i = 0; i <= 9; i++)
        {
            if (child->number[i] != NULL)
            {
                return root;
            }
        }

        // If no children, remove the node
        free(child);
        root->number[head->digit] = NULL;
    }

    // Recursively moves onto the next digit
    else
    {
        root->number[head->digit] = trie_delete(root->number[head->digit], head->next);
    }

    // check if the node has children
    for (int i = 0; i <= 9; i++)
    {
        if (root->number[i] != NULL)
        {
            return root;
        }
    }
    // if the root isn't an endpoint
    if (!root->end)
    {
        free(root);
        return NULL;
    }

    // if the root is an endpoint, return it
    return root;
}
