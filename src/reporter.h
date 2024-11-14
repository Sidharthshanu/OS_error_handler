// File: src/reporter.h
#ifndef REPORTER_H
#define REPORTER_H

#include "error_handler.h"

void report_error(ErrorType type, const char *message, int error_code);

#endif // REPORTER_H