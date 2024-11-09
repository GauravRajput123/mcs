/* Display all the files from current directory which are created in particular month */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

// Function to check if a file was created in the specified month and year
int file_created_in_month(const char *filename, int month, int year) {
    struct stat file_stat;
    struct tm *time_info;
    
    // Get file status
    if (stat(filename, &file_stat) != 0) {
        perror("stat");
        return 0;
    }
    
    // Convert creation time to local time
    time_info = localtime(&file_stat.st_ctime);
    
    // Check if the month and year match
    return (time_info->tm_mon + 1 == month) && (time_info->tm_year + 1900 == year);
}

int main(int argc, char *argv[]) {
    DIR *dir;
    struct dirent *entry;
    int month, year;

    // Check for correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <month> <year>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Parse month and year from command line arguments
    month = atoi(argv[1]);
    year = atoi(argv[2]);

    // Validate month and year
    if (month < 1 || month > 12 || year < 1900) {
        fprintf(stderr, "Invalid month or year.\n");
        return EXIT_FAILURE;
    }

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    printf("Files created in %02d/%d:\n", month, year);

    // Read directory entries
    while ((entry = readdir(dir)) != NULL) {
        // Skip directories
        if (entry->d_type == DT_REG) {
            if (file_created_in_month(entry->d_name, month, year)) {
                printf("%s\n", entry->d_name);
            }
        }
    }

    // Close directory
    closedir(dir);
    return EXIT_SUCCESS;
}