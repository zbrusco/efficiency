// Hash Table implementation that loads a dataset, searches and deletes specific values,
// and finally deletes the remainder of the dataset from memory

// Has time complexity for insertion, searching and deletion close to O(1) in this implementation
// In the worst case, it could have a time complexity for O(n) in all cases

// Currently the standard deviation for this specific program is σ = 0.007745 with a dataset of 50k numbers


#include "hashing.h"
// Function prototypes
unsigned int hash(int number);
void hash_delete(hashnode *n, hashnode *prev, int key);
void std_deviation(void);

// Global variables
unsigned int numberCount = 0;

// N is a prime number close to the size of the dataset
const unsigned int N = 9999991;

// Hash table
hashnode *table[N] = {NULL};

// Loads database into memory, returning true if successful, else false
bool hash_insert(const char *data_file)
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
        hashnode *n = calloc(1, sizeof(hashnode));
        if (n == NULL)
        {
            hash_unload();
            return false;
        }

        n->number = buffer;
        n->next = NULL;

        // hash word to obtain hash value
        unsigned int key = hash(n->number);
        numberCount++;

        // if at the start of the list
        if (table[key] == NULL)
        {
            table[key] = n;
        }

        // else just prepend to the head of the list
        else
        {
            n->next = table[key];
            table[key] = n;
        }
    }
    // Close the data file
    fclose(inptr);

    // Calculate the Std Deviation
    std_deviation();
    return true;
}

bool hash_search(int numbers)
{
    // Get hash value
    unsigned int key = hash(numbers);
    hashnode *prev = NULL;

    // Loop through the list at the key value
    for (hashnode *n = table[key]; n != NULL; n = n->next)
    {
        if (n->number == numbers)
        {
            // Delete N and return true
            hash_delete(n, prev, key);
            return true;
        }
        prev = n;
    }
    return false;
}

void hash_unload(void)
{
    // Iterating through the entire hash table
    for (int i = 0; i < N; i++)
    {
        // if head of list is found
        if (table[i] != NULL)
        {
            // reset head to null
            hashnode *head = table[i];
            table[i] = NULL;

            // free memory inside the linked list until all values are NULL
            while (head != NULL)
            {
                hashnode* cursor = head->next;
                free(head);
                head = cursor;
            }
        }
    }
}

unsigned int hash(int number)
{
    // Multiplying the number by a constant helps to produce a
    // more uniform distribution for a dataset that doesn't have many duplicate values

    // multiply the number by 2^32 * Phi (golden number)
    return (number * 2654435761) % N;
}

// Deletes number from the hash table
void hash_delete(hashnode *n, hashnode *prev, int key)
{
    // if head of the list
    if (prev == NULL)
    {
        table[key] = n->next;
    }
    // if in the middle of the list
    else
    {
        // skip N altogether
        prev->next = n->next;
    }
    free(n);
}

// Function that calculates the Std Deviation of the elements in the hash table
void std_deviation(void)
{
    // Calculate average X as the division of the number count by the amount of 'buckets'
    float Xm = (float) numberCount / N;
    // Sum of (Xi - Xm) squared
    float sum = 0;

    // Loop through the list at the key value
    for (int i = 0; i < N; i++)
    {
        float Xi = 0;
        // only check existing linked lists
        if (table[i] != NULL)
        {
            // access the head of the linked list
            hashnode *n = table[i];

            // free memory inside the linked list until all values are NULL
            while (n != NULL)
            {
                Xi++;
                n = n->next;
            }
            sum += (Xi - Xm) * (Xi - Xm);
        }
        else
        {
            sum += Xm*Xm;
        }
    }
    float result = sqrt(sum / (float) (N - 1));
    printf("     =============\n");
    printf("     STD DEVIATION\n");
    printf("     σ = %f\n", result);
    printf("     =============\n");
}
