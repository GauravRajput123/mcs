/*
Write a C program to find whether a given files passed through command line arguments are
present in current directory or not
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check if filenames are provided
    if (argc < 2) {
        printf("Ohhh Sorry You are not proving arguments..");
        return 1;
    }

    // Iterate through command line arguments
    for (int i = 1; i < argc; ++i) {
        FILE *file = fopen(argv[i], "r");

        if (file != NULL) {
            printf("%s is present in the current directory.\n", argv[i]);
            fclose(file);
        } else {
            printf("%s is not present in the current directory.\n", argv[i]);
        }
    }

    return 0;
}
















/*In window:
PS C:\Bootstrap Program> gcc Slip4A.c -o Slip4A
PS C:\Bootstrap Program> ./Slip4A Slip4A.c     

In Linux:
cc Slip4A.c
./a.out

Slip4A.c is present in the current directory.
*/
