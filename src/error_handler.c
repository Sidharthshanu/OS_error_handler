// File: src/error_handler.c
#include "error_handler.h"
#include "logger.h"
#include "reporter.h"
#include "recovery.h"
#include <stdio.h>
#include <stdlib.h>

// Function implementation
void handle_error(ErrorType type, const char *message, int error_code) {
    // Log the error
    log_error(type, message, error_code);

    // Report the error
    report_error(type, message, error_code);

    // Attempt recovery
    recover_from_error(type);
}