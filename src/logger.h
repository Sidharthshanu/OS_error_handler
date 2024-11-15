// File: src/logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include "error_handler.h"

void log_error(ErrorType type, const char *message, int error_code);

#endif // LOGGER_H