#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // Open a file for writing (or create it if it doesn't exist)
    int fileDescriptor = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fileDescriptor == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Redirect standard output to the file
    if (dup2(fileDescriptor, STDOUT_FILENO) == -1) {
        perror("Error redirecting standard output");
        close(fileDescriptor);
        exit(EXIT_FAILURE);
    }

    // Close the file descriptor, as dup2 duplicates the file descriptor
    close(fileDescriptor);

    // Now, standard output is redirected to the file
    printf("This will be written to output.txt\n");

    // Close standard output to prevent further writing to the file
    fclose(stdout);

    return 0;
}