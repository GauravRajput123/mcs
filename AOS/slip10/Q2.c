/* Generate parent process to write unnamed pipe and will write into it. Also generate child process which will read from pipe */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256

int main() 
{
    int pipe_fd[2];  // File descriptors for the pipe
    pid_t pid;
    char message[] = "Hello from parent!";
    char buffer[BUFFER_SIZE];

    // Create the pipe
    if (pipe(pipe_fd) == -1) 
   {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

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
        close(pipe_fd[1]); // Close unused write end

        // Read from pipe
        ssize_t bytes_read = read(pipe_fd[0], buffer, sizeof(buffer) - 1);
        if (bytes_read == -1) 
      {
            perror("read");
            exit(EXIT_FAILURE);
        }

        buffer[bytes_read] = '\0'; // Null-terminate the string
        printf("Child received: %s\n", buffer);

        close(pipe_fd[0]); // Close read end after reading
        exit(EXIT_SUCCESS);
    } else 
   {
        // Parent process
        close(pipe_fd[0]); // Close unused read end

        // Write to pipe
        ssize_t bytes_written = write(pipe_fd[1], message, strlen(message));
        if (bytes_written == -1) 
       {
            perror("write");
            exit(EXIT_FAILURE);
        }

        close(pipe_fd[1]); // Close write end after writing

        // Wait for child to complete
        wait(NULL);
    }

    return 0;
}