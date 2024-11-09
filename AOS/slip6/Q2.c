#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <unistd.h>

int main() {
    // Number of child processes to create
    int n = 5; // You can change this to the desired number of child processes

    clock_t start, end;
    struct tms start_tms, end_tms;

    // Record start time
    start = times(&start_tms);

    // Create n child processes
    for (int i = 0; i < n; ++i) {
        pid_t child_pid = fork();

        if (child_pid == -1) {
            perror("Fork failed");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {
            // Code for child process
            printf("Child %d started\n", i + 1);
            // Child-specific code goes here
            printf("Child %d finished\n", i + 1);
            exit(EXIT_SUCCESS);
        }
    }

    // Wait for all child processes to terminate
    for (int i = 0; i < n; ++i) {
        wait(NULL);
    }

    // Record end time
    end = times(&end_tms);

    // Calculate total user and kernel mode time
    clock_t user_time = end_tms.tms_utime - start_tms.tms_utime;
    clock_t sys_time = end_tms.tms_stime - start_tms.tms_stime;

    printf("Total User Time: %f seconds\n", (double)user_time / sysconf(_SC_CLK_TCK));
    printf("Total Kernel Time: %f seconds\n", (double)sys_time / sysconf(_SC_CLK_TCK));

    return 0;
}