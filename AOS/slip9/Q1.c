#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe_fd[2];
    pid_t child_pid;

    // Create the pipe
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    if ((child_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        close(pipe_fd[1]); // Close the write end of the pipe

        char buffer[100];
        ssize_t n;

        // Read messages from the pipe and print them
        while ((n = read(pipe_fd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[n] = '\0'; // Null-terminate the string
            printf("Child received: %s", buffer);
        }

        close(pipe_fd[0]); // Close the read end of the pipe
    } else {
        // Parent process
        close(pipe_fd[0]); // Close the read end of the pipe

        // Write messages to the pipe
        const char *messages[] = {
            "Hello from Parent - Message 1\n",
            "Hello from Parent - Message 2\n",
            "Hello from Parent - Message 3\n"
        };

        for (int i = 0; i < 3; ++i) {
            write(pipe_fd[1], messages[i], strlen(messages[i]));
        }

        close(pipe_fd[1]); // Close the write end of the pipe

        wait(NULL); // Wait for the child to finish
    }

    return 0;
}
