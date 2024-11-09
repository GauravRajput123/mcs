/* Display all the files from current directory whose size is greater that n Bytes Where n is accept from user. */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>

// Function to get the file size
off_t get_file_size(const char *filename) {
    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("stat");
        return -1;
    }
    return st.st_size;
}

int main(int argc, char *argv[]) {
    // Check if the size argument is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size_in_bytes>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Convert the size argument to an integer
    char *endptr;
    long size_threshold = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || size_threshold <= 0) {
        fprintf(stderr, "Invalid size: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    // Open the current directory
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    struct dirent *entry;

    printf("Files larger than %ld bytes:\n", size_threshold);

    // Read directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Check if the entry is a regular file
        if (entry->d_type == DT_REG) {
            off_t file_size = get_file_size(entry->d_name);
            if (file_size == -1) {
                closedir(dir);
                return EXIT_FAILURE;
            }
            if (file_size > size_threshold) {
                printf("%s (size: %ld bytes)\n", entry->d_name, file_size);
            }
        }
    }

    // Close the directory
    closedir(dir);

    return EXIT_SUCCESS;
}