/* Write a C program which create a child process which catch a signal sighup, sigint and sigquit. 
The Parent process send a sighup or sigint signal after every 3 seconds, at the end of 30 second 
parent send sigquit signal to child and child terminates my displaying message “My DADDY has Killed me!!!”. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>

void handle_sighup(int sig) {
    printf("Child: Received SIGHUP (signal %d)\n", sig);
}

void handle_sigint(int sig) {
    printf("Child: Received SIGINT (signal %d)\n", sig);
}

void handle_sigquit(int sig) {
    printf("Child: My DADDY has Killed me!!!\n");
    exit(0); // Terminate the child process
}

int main() {
    pid_t pid = fork(); // Create a child process

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) { // Child process
        // Set up signal handlers
        signal(SIGHUP, handle_sighup);
        signal(SIGINT, handle_sigint);
        signal(SIGQUIT, handle_sigquit);

        while (1) {
            pause(); // Wait for signals
        }
    } else { // Parent process
        printf("Parent process. Child PID: %d\n", pid);
        
        for (int i = 0; i < 10; i++) { // Send signals every 3 seconds for 30 seconds
            sleep(3);
            if (i % 2 == 0) {
                printf("Parent sending SIGHUP to child...\n");
                kill(pid, SIGHUP);
            } else {
                printf("Parent sending SIGINT to child...\n");
                kill(pid, SIGINT);
            }
        }

        // After 30 seconds, send SIGQUIT to the child
        printf("Parent sending SIGQUIT to child...\n");
        kill(pid, SIGQUIT);

        wait(NULL); // Wait for the child process to finish
    }

    return 0;
}