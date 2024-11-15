#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/file.h>

// Define LOCK macros if not available
#ifndef LOCK_EX
#define LOCK_EX 2
#endif

#ifndef LOCK_NB
#define LOCK_NB 4
#endif

#ifndef LOCK_UN
#define LOCK_UN 8
#endif

int main(void) {
    int fd = open("example.lock", O_CREAT | O_RDWR, 0666);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Lock the file exclusively and non-blocking
    if (flock(fd, LOCK_EX | LOCK_NB) == -1) {
        perror("flock");
        close(fd);
        return 1;
    }

    printf("File locked. Press Ctrl+C to exit or wait for 10000 seconds...\n");
    sleep(10000); // Simulate a long-running process

    // Unlock the file
    if (flock(fd, LOCK_UN) == -1) {
        perror("flock unlock");
    }
    close(fd);
    return 0;
}
