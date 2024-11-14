#include "error_handler.h"
#include "logger.h"
// Removed reporter.h include
#include "recovery.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function implementation
void handle_error(ErrorType type, const char *message, int error_code) {
    // Log the error
    log_error(type, message, error_code);

    // Report the error using Python script
    // Construct command to execute Python script with arguments
    char command[1024];
    // Adjust the path to the Python script as necessary
    snprintf(command, sizeof(command), "python3 src/report_error.py %d \"%s\" %d", type, message, error_code);
    
    // Execute the command
    int ret = system(command);
    if (ret != 0) {
        fprintf(stderr, "Failed to report error using Python script.\n");
    }

    // Attempt recovery
    recover_from_error(type);
}