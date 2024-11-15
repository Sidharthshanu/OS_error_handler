// File: src/logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include "error_handler.h"
#include <errno.h>   // Added for ETXTBSY if used in logger
#include <fcntl.h>   // Added for LOCK_EX, LOCK_NB, LOCK_UN if used in logger

void log_error(ErrorType type, const char *message, int error_code);

#endif // LOGGER_H