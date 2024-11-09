/*
Write a C program which creates a child process to run linux/ unix command or any user defined
program. The parent process set the signal handler for death of child signal and Alarm signal. If
a child process does not complete its execution in 5 second then parent process kills child process
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Global variable to track whether the child process has completed
int child_completed = 0;

// Signal handler for SIGCHLD (child process termination)
void sigchld_handler(int signum) {
    if (signum == SIGCHLD) {
        int status;
        pid_t pid = wait(&status);
        if (WIFEXITED(status)) {
            printf("Child process %d completed with exit status: %d\n", pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Child process %d terminated by signal: %d\n", pid, WTERMSIG(status));
        }
        child_completed = 1;
    }
}

// Signal handler for SIGALRM (timeout)
void sigalarm_handler(int signum) {
    if (signum == SIGALRM) {
        printf("Child process did not complete within the specified time. Killing the child process.\n");
        kill(0, SIGKILL);  // Kill the entire process group, including the child process
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s command [args...]\n", argv[0]);
        return 1;
    }

    // Set up signal handler for SIGCHLD
    signal(SIGCHLD, sigchld_handler);

    // Set up signal handler for SIGALRM
    signal(SIGALRM, sigalarm_handler);

    pid_t child_pid;

    // Create a child process
    if ((child_pid = fork()) == -1) {
        perror("fork");
        return 1;
    }

    if (child_pid == 0) {
        // Child process
        execvp(argv[1], &argv[1]);
        // execvp returns only if there is an error
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        // Set an alarm for 5 seconds
        alarm(5);

        // Wait for the child process to complete or be killed
        while (!child_completed) {
            // Do nothing, just wait
        }
    }

    return 0;
}