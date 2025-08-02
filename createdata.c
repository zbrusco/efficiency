// Simple C program that writes 'DATASET_SIZE' amount of numbers
// to a file chosen by the user.
// Does not overwrite existing files.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATASET_SIZE 10000000

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage ./createdata directory/[FILENAME]\n");
        return 1;
    }

    // check if that file exists
    FILE *dst = fopen(argv[1], "r");
    if (dst != NULL)
    {
        fclose(dst);
        printf("The filename %s is already being used!\n", argv[1]);
        return 2;
    }
    dst = fopen(argv[1], "w");

    if (dst == NULL)
    {
        printf("Could not open %s file!\n", argv[1]);
        return 3;
    }

    // seed the random function to get new values every time the program is run
    srand(time(NULL));

    for (int count = 0; count < DATASET_SIZE; count++)
    {
        int random = rand();
        fprintf(dst, "%d\n", random);
    }

    fclose(dst);
    return 0;
}
