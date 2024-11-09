/* Write a C program that illustrates suspending and resuming processes using signals */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void handle_signal(int signal) {
    // This function will handle signals sent to the child process
    if (signal == SIGSTOP) {
        printf("Child process received SIGSTOP signal. Suspending...\n");
    } else if (signal == SIGCONT) {
        printf("Child process received SIGCONT signal. Resuming...\n");
    }
}

int main() {
    pid_t pid = fork(); // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) { // Child process
        signal(SIGSTOP, handle_signal); // Set up signal handler for SIGSTOP
        signal(SIGCONT, handle_signal);  // Set up signal handler for SIGCONT

        while (1) { // Child process runs indefinitely
            printf("Child process is running. PID: %d\n", getpid());
            sleep(1); // Sleep for a second to simulate work
        }
    } else { // Parent process
        printf("Parent process. Child PID: %d\n", pid);
        sleep(3); // Let the child run for a few seconds

        // Send SIGSTOP to the child process
        printf("Parent sending SIGSTOP to child...\n");
        kill(pid, SIGSTOP);
        sleep(3); // Wait for 3 seconds while the child is suspended

        // Send SIGCONT to the child process
        printf("Parent sending SIGCONT to child...\n");
        kill(pid, SIGCONT);
        sleep(3); // Let the child run again

        // Terminate the child process
        printf("Parent terminating child process...\n");
        kill(pid, SIGTERM);
        wait(NULL); // Wait for the child process to finish
    }

    return 0;
}
