// Doubly Linked List that loads a dataset
// searches and deletes matching numbers and finally
// frees all memory allocated

// Allows insertion of O(1) when appending and prepending
// and O(n) for values in the middle of the list
// Search has efficiency of O(n)

// Essentially just as efficient as the SLL implemented before,
// albeit consumes more memory due to the aditional pointer for all elements


#include "doub_linkedlist.h"

// Global variables
dllnode *dllhead = NULL;
dllnode *dlltail = NULL;

// Inserts the dataset into the doubly linked list
bool dll_insert(const char *data_file)
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
            dllnode *n = malloc(sizeof(dllnode));
            if (n == NULL)
            {
                dll_unload();
                return false;
            }

            n->prev = NULL;
            n->next = NULL;
            n->number = buffer;

            // if list is empty
            if (dllhead == NULL)
            {
                dllhead = n;
                dlltail = n;
            }

            // If number belongs at beginning of list
            else if (n->number < dllhead->number)
            {
                n->next = dllhead;
                dllhead->prev = n;
                dllhead = n;
            }

            // If number is greater than or equal to
            // the tail, append to the end of the list
            else if (n->number >= dlltail->number)
            {
                dlltail->next = n;
                n->prev = dlltail;
                dlltail = n;
            }

            // If number belongs in the middle of the list
            else
            {
                // Iterate over nodes in list
                for (dllnode *cursor = dllhead; cursor != NULL; cursor = cursor->next)
                {
                    // if current number is smaller than the next number
                    if (n->number < cursor->next->number)
                    {
                        n->next = cursor->next;
                        n->prev = cursor;
                        cursor->next->prev = n;
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

// Searches a node to be deleted from the list
bool dll_search(int numbers)
{
    for (dllnode *n = dllhead; n != NULL; n = n->next)
    {
        if (n->number == numbers)
        {
            dll_delete(n);
            return true;
        }
    }
    return false;
}

// Unloads all memory allocated
void dll_unload(void)
{
    // access the head of the linked list
    dllnode *n = dllhead;

    // free memory inside the linked list until all values are NULL
    while (n != NULL)
    {
        dllnode *temp = n->next;
        free(n);
        n = temp;
    }
}

// Deletes a node from the list
void dll_delete(dllnode *n)
{
    // if n is head
    if (n->prev == NULL)
    {
        // if it's the last value
        if (n->next == NULL)
        {
            // reset head and tail back to null
            dllhead = NULL;
            dlltail = NULL;
        }
        // if there are other values
        else
        {
            // move the head pointer to the next value
            dllhead = n->next;
            // reset head prev pointer to null
            dllhead->prev = NULL;
        }

        free(n);
    }
    // if n is tail
    else if(n->next == NULL)
    {
        dlltail = n->prev;
        dlltail->next = NULL;
        free(n);
    }
    else
    {
        n->prev->next = n->next;
        n->next->prev = n->prev;
        free(n);
    }
}
