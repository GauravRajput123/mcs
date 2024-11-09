#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

volatile sig_atomic_t counter = 0;

void handle_sigusr1(int signo) {
    // Custom signal handler for SIGUSR1
    printf("Child Process: Received SIGUSR1 signal. Suspending...\n");
    pause(); // Suspend the process until SIGCONT is received
    printf("Child Process: Resumed. Continuing...\n");
}

int main() {
    pid_t child_pid;

    // Install a custom signal handler for SIGUSR1
    signal(SIGUSR1, handle_sigusr1);

    // Fork a child process
    if ((child_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) { // Inside the child process
        while (1) {
            // Child process main loop
            printf("Child Process: Counter = %d\n", counter);
            sleep(1);
            counter++;
        }
    } else { // Inside the parent process
        // Wait for a moment to let the child start
        sleep(2);

        // Send SIGUSR1 to the child to trigger suspension
        kill(child_pid, SIGUSR1);

        // Wait for a moment to observe the child being suspended
        sleep(3);

        // Send SIGCONT to the child to resume it
        kill(child_pid, SIGCONT);

        // Let the child run for a while
        sleep(5);

        // Send SIGTERM to terminate the child process
        kill(child_pid, SIGTERM);
    }

    return 0;
}