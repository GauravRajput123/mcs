
/*
Write a C program to find file properties such as inode number, number of hard link, File
permissions, File size, File access and modification time and so on of a given file using stat()
system call
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>


int main(int argc, char *argv[]) {
    // Check if a filename is provided
    if (argc < 2) {
        printf("Ohhh Sorry You are not proving arguments..");
        return 1;
    }

    const char *file_path = argv[1];
 struct stat file_stat;

    // Get file information
    if (stat(file_path, &file_stat) == 0) {
        // Print file properties
        printf("File Properties for: %s\n", file_path);
        printf("Inode Number: %d\n", file_stat.st_ino);
        printf("Number of Hard Links: %d\n", file_stat.st_nlink);
        printf("File Permissions: %d\n", file_stat.st_mode & 0777); // File permission bits
        printf("File Size: %d bytes\n", file_stat.st_size);
        printf("Last Access Time: %s", ctime(&file_stat.st_atime));
        printf("Last Modification Time: %s", ctime(&file_stat.st_mtime));
    } else {
        // Print an error message if stat fails
        perror(file_path);
    }
    return 0;
}












/*
PS C:\Bootstrap Program> gcc Slip2A.c -o Slip2A
PS C:\Bootstrap Program> ./Slip2A Slip2A.c    
 
File Properties for: Slip2A.c
Inode Number: 0
Number of Hard Links: 1
File Permissions: 438
File Size: 1300 bytes
Last Access Time: Sun Dec 10 15:11:04 2023
Last Modification Time: Sun Dec 10 15:11:04 2023
*/