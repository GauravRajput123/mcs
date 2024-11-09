#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];
    pid_t child_ls_pid, child_wc_pid;

    // Create pipe
    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    // Fork first child for ls -l
    child_ls_pid = fork();

    if (child_ls_pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_ls_pid == 0) {
        // Child process for ls -l
        close(pipe_fd[0]); // Close read end of the pipe
        dup2(pipe_fd[1], STDOUT_FILENO); // Redirect standard output to the pipe write end

        // Execute ls -l
        execlp("ls", "ls", "-l", NULL);
        perror("Exec failed");
        exit(EXIT_FAILURE);
    }

    // Fork second child for wc -l
    child_wc_pid = fork();

    if (child_wc_pid == -1) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (child_wc_pid == 0) {
        // Child process for wc -l
        close(pipe_fd[1]); // Close write end of the pipe
        dup2(pipe_fd[0], STDIN_FILENO); // Redirect standard input to the pipe read end

        // Execute wc -l
        execlp("wc", "wc", "-l", NULL);
        perror("Exec failed");
        exit(EXIT_FAILURE);
    }

    // Close unused pipe ends in the parent process
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for both child processes to finish
    wait(NULL);
    wait(NULL);

    return 0;
}