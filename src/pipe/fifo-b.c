#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO_PATH "/tmp/myfifo"

int main() {
    int fd;
    char buffer[100];

    // Create FIFO (ignore error if it already exists)
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        perror("mkfifo");
    }

    fd = open(FIFO_PATH, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    read(fd, buffer, sizeof(buffer));
    printf("Received: %s\n", buffer);

    close(fd);
    return 0;
}
