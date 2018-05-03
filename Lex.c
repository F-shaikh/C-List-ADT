//-----------------------------------------------------------------------------
// FileIO.c
// Illustrates file input-output commands and text processing using the
// string functions strtok and strcat.
//-----------------------------------------------------------------------------
#include "List.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LEN 160

int main(int argc, char * argv[])
{
    FILE *in, *out;
    char line[MAX_LEN];
    int myLines = 0;
    // check command line for correct number of arguments
    if (argc != 3)
    {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    // open files for reading and writing
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if (in == NULL)
    {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if (out == NULL)
    {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    /* read each line of input file, then count and print tokens */
    while(fgets(line, MAX_LEN, in) != NULL)
    {
        myLines++;
    }
    rewind(in);
    char *array[myLines];

    for(int i = 0; i < myLines; i++)
    {
        fgets(line,MAX_LEN,in);
        array[i] = (char*) malloc(sizeof(line));
        strcpy(array[i],line);
    }
    List list = newList();
    int flag = 1;
    append(list,0); // Starting point for comparison.
    for (int i = 1; i < myLines; i++)
    {
        moveFront(list);
        flag = 1;
        while (index(list) != -1 && flag == 1)
        {
            if (strcmp(array[get(list)], array[i]) > 0)
            {
                insertBefore(list, i);
                flag = 0;
            }
            else
            {
                moveNext(list);
            }
        }
        if (index(list) == -1)
        {
            append(list,i);
        }
    }
    moveFront(list);
    while(index(list) != -1)
    {
        fprintf(out, array[get(list)]);
        moveNext(list);
    }

    for(int i = 0; i< myLines; i++)
    {
        free(array[i]);
    }
    freeList(&list);
    /* close files */
    fclose(in);
    fclose(out);
    return (0);
}
