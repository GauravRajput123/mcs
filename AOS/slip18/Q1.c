/* Write a C program to find whether a given file is present in current directory or not */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    // Check if the filename argument is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename_to_find = argv[1];

    // Open the current directory
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    struct dirent *entry;
    int file_found = 0;

    // Read directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Compare the entry name with the filename to find
        if (strcmp(entry->d_name, filename_to_find) == 0) {
            file_found = 1;
            break;
        }
    }

    // Close the directory
    closedir(dir);

    // Print the result
    if (file_found) {
        printf("File '%s' is present in the current directory.\n", filename_to_find);
    } else {
        printf("File '%s' is not present in the current directory.\n", filename_to_find);
    }

    return EXIT_SUCCESS;
}
