// File: src/simulations/simulate_device_error.c
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "error_handler.h"

int main() {
    printf("Simulating device access error...\n");
    int fd = open("/dev/nonexistent_device", O_RDONLY);
    if (fd == -1) {
        printf("Device Error: %s\n", strerror(errno));
        handle_error(DEVICE_ERROR, strerror(errno), errno);
        return errno;
    }
    close(fd);
    return 0;
}