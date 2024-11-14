// File: src/error_handler.c
#include "error_handler.h"
#include "logger.h"
#include "recovery.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void handle_error(ErrorType type, const char *message, int error_code) {
    // Log the error
    printf("Error for debugging purpose: %s\n", message);
    log_error(type, message, error_code);

    pid_t pid = fork();
    if (pid == 0) {
        // Child process

        // Prepare arguments
        char type_str[10];
        char error_code_str[10];
        snprintf(type_str, sizeof(type_str), "%d", type);
        snprintf(error_code_str, sizeof(error_code_str), "%d", error_code);

        // Ensure the path to the Python script is correct.
        // Here, it's assumed that the executable is run from the project root.
        char *args[] = {
            "python3",
            "./dashboard/report_error.py", // Updated path to the Python script
            type_str,
            (char *)message,
            error_code_str,
            NULL
        };
        
        // Execute the Python script
        execvp("python3", args);
        
        // If execvp returns, an error occurred
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Fork failed
        perror("fork failed");
        fprintf(stderr, "Failed to report error using Python script.\n");
    } else {
        // Parent process: wait for child if necessary
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid failed");
        } else {
            if (WIFEXITED(status)) {
                if (WEXITSTATUS(status) != 0) {
                    fprintf(stderr, "Python script exited with status %d.\n", WEXITSTATUS(status));
                }
            } else if (WIFSIGNALED(status)) {
                fprintf(stderr, "Python script terminated by signal %d.\n", WTERMSIG(status));
            } else {
                fprintf(stderr, "Python script did not terminate normally.\n");
            }
        }
    }

    // Attempt recovery
    recover_from_error(type);
}