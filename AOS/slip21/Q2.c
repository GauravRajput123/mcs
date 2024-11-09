/* Write a C program which receives file names as command line arguments and display those filenames in ascending order according to their sizes. I) (e.g $ a.out a.txt b.txt c.txt, …) */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

typedef struct {
    char *filename;
    off_t size;
} FileInfo;

// Comparison function for qsort
int compare(const void *a, const void *b) {
    FileInfo *fileA = (FileInfo *)a;
    FileInfo *fileB = (FileInfo *)b;
    return (fileA->size - fileB->size);
}

// Function to get file size
off_t get_file_size(const char *filename) {
    struct stat st;
    if (stat(filename, &st) != 0) {
        perror("stat");
        return -1;
    }
    return st.st_size;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> <file2> ...\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Allocate memory for FileInfo array
    FileInfo *files = malloc((argc - 1) * sizeof(FileInfo));
    if (files == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    // Fill FileInfo array
    for (int i = 1; i < argc; i++) {
        files[i - 1].filename = argv[i];
        files[i - 1].size = get_file_size(argv[i]);
        if (files[i - 1].size == -1) {
            free(files);
            return EXIT_FAILURE;
        }
    }

    // Sort files based on size
    qsort(files, argc - 1, sizeof(FileInfo), compare);

    // Print sorted filenames
    printf("Files sorted by size:\n");
    for (int i = 0; i < argc - 1; i++) {
        printf("%s (size: %ld bytes)\n", files[i].filename, files[i].size);
    }

    // Free allocated memory
    free(files);

    return EXIT_SUCCESS;
}