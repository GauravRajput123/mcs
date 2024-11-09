/*
Write a C program to create an unnamed pipe. The child process will write following three
messages to pipe and parent process display it.
Message1 = “Hello World”
Message2 = “Hello SPPU”
Message3 = “Linux is Funny” 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
        close(pipe_fd[0]); // Close the read end of the pipe

        // Write messages to the pipe
        const char *messages[] = {"Hello World\n", "Hello SPPU\n", "Linux is Funny\n"};
        for (int i = 0; i < 3; ++i) {
            write(pipe_fd[1], messages[i], strlen(messages[i]));
        }

        close(pipe_fd[1]); // Close the write end of the pipe in the child
    } else {
        // Parent process
        close(pipe_fd[1]); // Close the write end of the pipe

        // Read and display messages from the pipe
        char buffer[1024];
        ssize_t n;
        while ((n = read(pipe_fd[0], buffer, sizeof(buffer))) > 0) {
            write(STDOUT_FILENO, buffer, n);
        }

        close(pipe_fd[0]); // Close the read end of the pipe in the parent
        wait(NULL); // Wait for the child to complete
    }

    return 0;
}
