/* Write a C program that print the exit status of a terminated child process */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() 
{
    pid_t pid;
    int status;

    // Fork a new process
    pid = fork();
    if (pid == -1) 
   {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) 
   {
        // Child process
        printf("Child process: PID %d\n", getpid());
        // Exit with a specific status code
        exit(42); // You can choose any exit status code here
    } else 
   {
        // Parent process
        pid_t terminated_pid;

        // Wait for the child process to terminate
        terminated_pid = waitpid(pid, &status, 0);
        if (terminated_pid == -1) 
       {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) 
       {
            // Print the exit status of the child process
            int exit_status = WEXITSTATUS(status);
            printf("Child process with PID %d terminated with exit status %d\n", terminated_pid, exit_status);
        } else 
       {
            // Handle the case where the child did not exit normally
            printf("Child process with PID %d did not terminate normally\n", terminated_pid);
        }
    }

    return 0;
}