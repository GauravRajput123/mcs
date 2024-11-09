#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void print_limits() {
    struct rlimit limits;

    // Get the current resource limits for the process
    if (getrlimit(RLIMIT_NOFILE, &limits) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    // Display the current file limit
    printf("Current file limit: %lld\n", (long long)limits.rlim_cur);

    // Set a new file limit (e.g., 1024)
    limits.rlim_cur = 1024;

    // Set the new file limit for the process
    if (setrlimit(RLIMIT_NOFILE, &limits) == -1) {
        perror("setrlimit");
        exit(EXIT_FAILURE);
    }

    // Get the updated resource limits
    if (getrlimit(RLIMIT_NOFILE, &limits) == -1) {
        perror("getrlimit");
        exit(EXIT_FAILURE);
    }

    // Display the updated file limit
    printf("Updated file limit: %lld\n", (long long)limits.rlim_cur);
}

int main() {
    print_limits();

    return 0;
}