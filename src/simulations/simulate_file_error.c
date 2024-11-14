// File: src/simulations/simulate_file_error.c
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "error_handler.h"

int main() {
    printf("Simulating file access error...\n");
    FILE *file = fopen("/path/to/nonexistent/file.txt", "r");
    if (file == NULL) {
        printf("File Access Error: %s\n", strerror(errno));
        handle_error(FILE_ACCESS_ERROR, strerror(errno), errno);
        return errno;
    }
    fclose(file);
    return 0;
}