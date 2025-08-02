// C program to test efficiency of different structures
// with large datasets
// Usage ./efficiency dataset/file.txt numbers/file.txt [structure]
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>

// Include structure headers
#include "sing_linkedlist.h"
#include "doub_linkedlist.h"
#include "bst.h"
#include "avl_tree.h"
#include "hashing.h"
#include "trie.h"

// Default database
#define DATABASE "dataset/random.txt"


// Function prototypes
double calculate(const struct rusage *b, const struct rusage *a);

typedef struct {
    bool (*insert)(const char *filename);
    bool (*search)(int number);
    void (*unload)(void);
} structure_ops;


int main(int argc, char *argv[])
{
    if (argc != 3 && argc != 4)
    {
        printf("Usage: ./efficiency dataset/file search/file structure\n");
        return 1;
    }

    // Structures for timing data
    struct rusage before, after;

    // Benchmarks
    double time_load = 0.0, time_check = 0.0, time_unload = 0.0;

    // Determine dataset and structure to use
    char *data = (argc == 4) ? argv[1] : DATABASE;
    char *structure = (argc == 4) ? argv[3] : argv[2];

    // Match structure with appropriate functions
    structure_ops ops;
    if (strcmp(structure, "sll") == 0)
    {
        ops.insert = sll_insert;
        ops.search = sll_search;
        ops.unload = sll_unload;
    }
    else if (strcmp(structure, "dll") == 0)
    {
        ops.insert = dll_insert;
        ops.search = dll_search;
        ops.unload = dll_unload;
    }
    else if (strcmp(structure, "bst") == 0)
    {
        ops.insert = bst_insert;
        ops.search = bst_search;
        ops.unload = bst_unload;
    }
    else if (strcmp(structure, "avl") == 0)
    {
        ops.insert = avl_insert;
        ops.search = avl_search;
        ops.unload = avl_unload;
    }
    else if (strcmp(structure, "h") == 0)
    {
        ops.insert = hash_insert;
        ops.search = hash_search;
        ops.unload = hash_unload;
    }
    else if (strcmp(structure, "t") == 0)
    {
        ops.insert = trie_insert;
        ops.search = trie_search;
        ops.unload = trie_unload;
    }
    else
    {
        printf("Unknown structure: %s\n", structure);
        return 1;
    }

    // Load database into structure
    getrusage(RUSAGE_SELF, &before);
    bool loaded = ops.insert(data);
    getrusage(RUSAGE_SELF, &after);
    printf("Insertion Finished\n");


    // Exit if database not loaded
    if (!loaded)
    {
        printf("Could not load %s.\n", data);
        return 1;
    }

    // Calculate time to load database
    time_load = calculate(&before, &after);

    // Try to open dataset
    char *text = (argc == 4) ? argv[2] : argv[1];
    FILE *file = fopen(text, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", text);
        sll_unload();
        return 1;
    }

    int numbers;
    int numberCount = 0, notFound = 0;

    // read numbers from dataset one at a time
    while (fscanf(file, "%i", &numbers) == 1)
    {
        numberCount++;
        getrusage(RUSAGE_SELF, &before);
        bool found = ops.search(numbers);
        getrusage(RUSAGE_SELF, &after);
        time_check += calculate(&before, &after);

        if (!found)
        {
            //printf("Number not found: %d\n", numbers);
            notFound++;
        }
    }

    // Unload database
    getrusage(RUSAGE_SELF, &before);
    ops.unload();
    getrusage(RUSAGE_SELF, &after);

    // Calculate time to unload database
    time_unload = calculate(&before, &after);

    // Check whether there was an error
    if (ferror(file))
    {
        fclose(file);
        printf("Error reading %i.\n", numbers);
        ops.unload();
        return 1;
    }

    // Close text
    fclose(file);

    // Print results
    printf("\n=== TESTING %s EFFICIENCY ===\n", structure);
    printf("NUMBERS NOT FOUND:   %d\n", notFound);
    printf("NUMBERS CHECKED:     %d\n", numberCount);
    printf("\nTIMES (for %s)\n", structure);
    printf("TIME IN INSERTION:   %.6f seconds\n", time_load);
    printf("TIME IN SEARCH:      %.6f seconds\n", time_check);
    printf("TIME IN UNLOAD:      %.6f seconds\n", time_unload);
    printf("TIME IN TOTAL:       %.6f seconds\n\n", time_load + time_check + time_unload);


    return 0;
}

// Returns number of seconds between b and a
double calculate(const struct rusage *b, const struct rusage *a)
{
    if (b == NULL || a == NULL)
    {
        return 0.0;
    }
    else
    {
        return ((((a->ru_utime.tv_sec * 1000000 + a->ru_utime.tv_usec) -
                  (b->ru_utime.tv_sec * 1000000 + b->ru_utime.tv_usec)) +
                 ((a->ru_stime.tv_sec * 1000000 + a->ru_stime.tv_usec) -
                  (b->ru_stime.tv_sec * 1000000 + b->ru_stime.tv_usec)))
                / 1000000.0);
    }
}
