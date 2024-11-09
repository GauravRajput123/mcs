/* Write a C program to implement the following unix/linux command (use fork, pipe and exec system call). 
Your program should block the signal Ctrl-C and Ctrl-\ signal during the execution. i. ls –l | wc –l */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

void block_signals() 
{
    sigset_t new_set, old_set;

    // Initialize the signal set
    sigemptyset(&new_set);

    // Add SIGINT and SIGQUIT to the set
    sigaddset(&new_set, SIGINT);
    sigaddset(&new_set, SIGQUIT);

    // Block the signals
    if (sigprocmask(SIG_BLOCK, &new_set, &old_set) == -1) 
   {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }
}

void unblock_signals() 
{
    sigset_t old_set;

    // Unblock the signals
    if (sigprocmask(SIG_UNBLOCK, NULL, &old_set) == -1) 
   {
        perror("sigprocmask");
        exit(EXIT_FAILURE);
    }
}

int main() {
    int pipe_fd[2];
    pid_t pid1, pid2;

    // Create the pipe
    if (pipe(pipe_fd) == -1) 
   {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Block SIGINT and SIGQUIT
    block_signals();

    // Fork the first child to run 'ls -l'
    pid1 = fork();
    if (pid1 == -1) 
   {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) 
   {
        // Child 1: Execute 'ls -l'
        close(pipe_fd[0]); // Close unused read end
        dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe write end
        close(pipe_fd[1]); // Close the original write end after redirection

        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Fork the second child to run 'wc -l'
    pid2 = fork();
    if (pid2 == -1) 
   {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) 
   {
        // Child 2: Execute 'wc -l'
        close(pipe_fd[1]); // Close unused write end
        dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to pipe read end
        close(pipe_fd[0]); // Close the original read end after redirection

        execlp("wc", "wc", "-l", (char *)NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Parent process
    close(pipe_fd[0]); // Close pipe read end in parent
    close(pipe_fd[1]); // Close pipe write end in parent

    // Wait for both child processes to complete
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    // Unblock SIGINT and SIGQUIT
    unblock_signals();

    return 0;
}
