/*
Print the type of file and inode number where file name accepted through Command Line
*/
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


/* OUTPUT:

PS C:\Bootstrap Program> gcc Slip1A.c -o Slip1A
PS C:\Bootstrap Program> ./Slip1A Slip1A.c
Inode number of Slip1A.c: 0
Slip1A.c is a regular file.

*/  

