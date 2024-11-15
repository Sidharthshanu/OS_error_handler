#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>

int main(void) {
    int fd = open("build/example.lock", O_CREAT | O_RDWR);
    if (fd == -1) {
        perror("");
        printf("%d",errno);
        return 1;
    }

    if (flock(fd, LOCK_EX | LOCK_NB) == -1) { // Lock the file exclusively
        perror("flock");
        close(fd);
        return 1;
    }

    sleep(10000);
    flock(fd, LOCK_UN); // Unlock the file
    close(fd);
    return 0;
}