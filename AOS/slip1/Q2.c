/*
Write a C program to send SIGALRM signal by child process to parent process and parent process
make a provision to catch the signal and display alarm is fired.(Use Kill, fork, signal and sleep
system call)
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Signal handler function
void alarm_handler(int signum) {
    if (signum == SIGALRM) {
        printf("Alarm is fired!\n");
    }
}

int main() {
    pid_t child_pid;

    // Set up signal handler
    signal(SIGALRM, alarm_handler);

    // Create a child process
    if ((child_pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        // Sleep for 2 seconds and then send SIGALRM to parent
        sleep(2);
        kill(getppid(), SIGALRM);
    } else {
        // Parent process
        printf("Waiting for the alarm...\n");

        // Sleep indefinitely to allow time for the child to send the signal
        while (1) {
            sleep(1);
        }
    }

    return 0;
}