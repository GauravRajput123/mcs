/*
Write a C program that catches the ctrl-c (SIGINT) signal for the first time and display the
appropriate message and exits on pressing ctrl-c again  
*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

// Global variable to track whether SIGINT has been received
int sigint_received = 0;

// Signal handler function for SIGINT
void sigint_handler(int signum) {
    if (signum == SIGINT) {
        if (!sigint_received) {
            printf("Ctrl+C (SIGINT) received. Press again to exit.\n");
            sigint_received = 1;
        } else {
            printf("Ctrl+C (SIGINT) received again. Exiting...\n");
            exit(EXIT_SUCCESS);
        }
    }
}

int main() {
    // Set up signal handler for SIGINT
    signal(SIGINT, sigint_handler);

    // Loop indefinitely
    while (1) {
        // Do some work or sleep here
    }

    return 0;
}