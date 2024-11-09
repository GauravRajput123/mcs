/*Write a C program which creates a child process and child process catches a signal SIGHUP,
SIGINT and SIGQUIT. The Parent process send a SIGHUP or SIGINT signal after every 3
seconds, at the end of 15 second parent send SIGQUIT signal to child and child terminates by
displaying message "My Papa has Killed me!!!”
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sighup_handler(int signum) {
    if (signum == SIGHUP) {
        printf("Child process received SIGHUP.\n");
    }
}

void sigint_handler(int signum) {
    if (signum == SIGINT) {
        printf("Child process received SIGINT.\n");
    }
}

void sigquit_handler(int signum) {
    if (signum == SIGQUIT) {
        printf("Child process received SIGQUIT. My Papa has killed me!!!\n");
        exit(EXIT_SUCCESS);
    }
}

int main() {
    pid_t child_pid;

    // Create a child process
    if ((child_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        // Set up signal handlers
        signal(SIGHUP, sighup_handler);
        signal(SIGINT, sigint_handler);
        signal(SIGQUIT, sigquit_handler);

        // Infinite loop to keep the child process running
        while (1) {
            sleep(1);
        }
    } else {
        // Parent process
        // Send SIGHUP or SIGINT to the child every 3 seconds for 12 seconds
        for (int i = 0; i < 4; ++i) {
            sleep(3);
            if (i % 2 == 0) {
                kill(child_pid, SIGHUP);
            } else {
                kill(child_pid, SIGINT);
            }
        }

        // After 15 seconds, send SIGQUIT to terminate the child
        sleep(3);
        kill(child_pid, SIGQUIT);

        // Wait for the child to terminate
        wait(NULL);
    }

    return 0;
}