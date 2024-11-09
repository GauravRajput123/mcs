/* Write a program that illustrates how to execute two commands concurrently with a pipe. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main() {
    int pipefd[2];
    pid_t pid1, pid2;

    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork the first child process
    if ((pid1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // Child process 1
        // Close unused write end of the pipe
        close(pipefd[1]);

        // Redirect standard input to the read end of the pipe
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        // Execute the second command: `grep a`
        execlp("grep", "grep", "a", NULL);

        // If exec fails
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {
        // Fork the second child process
        if ((pid2 = fork()) == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid2 == 0) {
            // Child process 2
            // Close unused read end of the pipe
            close(pipefd[0]);

            // Redirect standard output to the write end of the pipe
            dup2(pipefd[1], STDOUT_FILENO);
            close(pipefd[1]);

            // Execute the first command: `ls`
            execlp("ls", "ls", NULL);

            // If exec fails
            perror("execlp");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            // Close both ends of the pipe
            close(pipefd[0]);
            close(pipefd[1]);

            // Wait for both child processes to finish
            wait(NULL);
            wait(NULL);
        }
    }

    return 0;
}