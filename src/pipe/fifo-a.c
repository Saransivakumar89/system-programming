#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_PATH "/tmp/myfifo"

int main() {
    int fd;
    char *msg = "Hello";

    fd = open(FIFO_PATH, O_WRONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    write(fd, msg, strlen(msg) + 1);

    close(fd);
    return 0;
}
