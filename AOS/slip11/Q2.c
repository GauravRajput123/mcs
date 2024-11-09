/* Write a C program that redirects standard output to a file output.txt. (use of dup and open system call). */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;

    // Open or create the file "output.txt" for writing
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // Check if file open was successful
    if (fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }

    // Duplicate the file descriptor for standard output
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("dup2");
        close(fd); // Close the file descriptor before exiting
        return EXIT_FAILURE;
    }

    // Close the original file descriptor as it's no longer needed
    close(fd);

    // Now, anything printed to stdout will go to "output.txt"
    printf("This message is written to output.txt.\n");
    printf("Another line of output to the file.\n");

    return EXIT_SUCCESS;
}