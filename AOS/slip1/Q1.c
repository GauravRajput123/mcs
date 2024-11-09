/*
Take multiple files as Command Line Arguments and
 print their inode numbers and file types
 Program Name : Slip1A.c
*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    // Check if a filename is provided
    if (argc < 2) {
        printf("Ohhh Sorry You are not proving arguments..");
        return 1;
    }

     char *file_path = argv[1];
     struct stat file_stat;

    // Get file information
    if (stat(file_path, &file_stat) == 0) 
    {
        ino_t inode_number = file_stat.st_ino;

        // Print the inode number
        printf("Inode number of %s: %d\n", file_path, inode_number);
        // Determine file type
        if (S_ISREG(file_stat.st_mode))
           {
             printf("%s is a regular file.\n", file_path);
           }
        else if (S_ISDIR(file_stat.st_mode))
           {
             printf("%s is a directory.\n", file_path);
           }
           else
            {
              printf("%s is of unknown type.\n", file_path);
            }
    }
     else {
        // Print an error message if stat fails
        perror(file_path);
        return 1;
    }


    return 0;
}




/* Take multiple files as Command Line Arguments and print their 
inode numbers and file types */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// Function to print the file type based on the st_mode field
const char* file_type(mode_t mode) 
{
    if (S_ISREG(mode)) return "Regular File";
    if (S_ISDIR(mode)) return "Directory";
    if (S_ISCHR(mode)) return "Character Device";
    if (S_ISBLK(mode)) return "Block Device";
    if (S_ISFIFO(mode)) return "FIFO/Pipe";
    if (S_ISLNK(mode)) return "Symbolic Link";
    if (S_ISSOCK(mode)) return "Socket";
    return "Unknown";
}

int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) 
   {
        struct stat file_stat;

        if (stat(argv[i], &file_stat) == -1) 
       {
            perror(argv[i]);
            continue;
        }

        printf("File: %s\n", argv[i]);
        printf("Inode Number: %lu\n", (unsigned long)file_stat.st_ino);
        printf("File Type: %s\n", file_type(file_stat.st_mode));
        printf("\n");
    }
    return EXIT_SUCCESS;
}
