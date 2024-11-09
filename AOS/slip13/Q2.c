#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <prefix>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *prefix = argv[1];

    // Open the current directory
    DIR *dir = opendir(".");

    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    // Read the directory entries
    struct dirent *entry;
    printf("Files with prefix \"%s\":\n", prefix);

    while ((entry = readdir(dir)) != NULL) {
        // Check if the entry matches the prefix
        if (strncmp(entry->d_name, prefix, strlen(prefix)) == 0) {
            printf("%s\n", entry->d_name);
        }
    }

    // Close the directory
    closedir(dir);

    return 0;
}




