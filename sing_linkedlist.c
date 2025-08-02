// Singly Linked List that loads a dataset
// searches and deletes matching numbers and finally
// frees all memory allocated

// Allows insertion of O(1) when appending and prepending
// and O(n) for values in the middle of the list
// Search has efficiency of O(n)

// Just as efficient as DLL, but with simpler logic.
// there's no need to traverse the list once again
// if you track the current and previous pointer at deletion

#include "sing_linkedlist.h"


// Global Variables
node *head = NULL;
node *tail = NULL;

// Inserts the dataset into the singly linked list
bool sll_insert(const char *data_file)
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
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            sll_unload();
            return false;
        }

        n->next = NULL;
        n->number = buffer;

        // if list is empty
        if (head == NULL)
        {
            head = n;
            tail = n;
        }

        // If number belongs at beginning of list
        else if (n->number < head->number)
        {
            n->next = head;
            head = n;
        }

        // If number is greater than or equal to
        // the tail, append to the end of the list
        else if (n->number >= tail->number)
        {
            tail->next = n;
            tail = n;
        }

        // If number belongs in the middle of the list
        else
        {
            // Iterate over nodes in list
            for (node *cursor = head; cursor != NULL; cursor = cursor->next)
            {
                // if current number is smaller than the next number
                if (n->number < cursor->next->number)
                {
                    n->next = cursor->next;
                    cursor->next = n;
                    break;
                }
            }
        }
    }
    // Close the data file
    fclose(inptr);

    return true;
}

// Searches a node in the list
bool sll_search(int numbers)
{
    for (node *n = head, *prev = head; n != NULL; n = n->next)
    {
        if (n->number == numbers)
        {
            sll_delete(n, prev);
            return true;
        }
        prev = n;
    }
    return false;
}

// Unloads all memory allocated
void sll_unload(void)
{
    // access the head of the linked list
    node *n = head;

    // free memory inside the linked list until all values are NULL
    while (n != NULL)
    {
        node *temp = n->next;
        free(n);
        n = temp;
    }
}

// Deletes a node from the list
void sll_delete(node *n, node *prev)
{
    // edge case if n is head
    if (n == prev)
    {
        head = n->next;
        free(n);
    }
    // edge case if n is tail
    else if (n->next == NULL)
    {
        prev->next = NULL;
        free(n);
    }
    else
    {
        prev->next = n->next;
        free(n);
    }
}
