/*Read the current directory and 
display the name of the files, no of files in current directory
*/

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    int file_count = 0;

    // Open the current directory
    if ((dir = opendir(".")) != NULL) {
        // Iterate through directory entries
        while ((entry = readdir(dir)) != NULL) {
            // Display file name
            printf("%s\n", entry->d_name);
            
            // Count files
            if (entry->d_type == DT_REG) {
                file_count++;
            }
        }

        // Close the directory
        closedir(dir);

        // Display the total number of files
        printf("Total number of files: %d\n", file_count);
    } else {
        // Print an error message if opendir fails
        perror("opendir");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}














/*
.
..
cinode.c
cinode.exe
h1.html
Slip1A.c
Slip1A.exe
Slip1B.c
Slip2A.c
*/
