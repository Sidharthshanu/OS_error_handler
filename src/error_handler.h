// File: src/error_handler.h
#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

typedef enum {
    MEMORY_ERROR,
    FILE_ACCESS_ERROR,
    DEVICE_ERROR,
    NULL_ERROR,       // Added NULL_ERROR for null pointer dereference
    UNKNOWN_ERROR,
    TXT_BUSY, // Added new Device errors
    DEVICE_ERROR_ACCESS_FAILURE,
    DEVICE_BUSY
} ErrorType;

// Function to handle errors
void handle_error(ErrorType type, const char *message, int error_code);

#endif // ERROR_HANDLER_H