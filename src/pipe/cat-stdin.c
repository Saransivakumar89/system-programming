#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void) {
    int fd;
    char buffer[1024];
    ssize_t n;

    fd = open("output.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return -1;
    }

    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("dup2");
        close(fd);
        return -1;
    }
    close(fd); 

    while ((n = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
        if (write(STDOUT_FILENO, buffer, n) != n) {
            perror("write");
            return -1;
        }
    }

    if (n == -1) {
        perror("read");
        return -1;
    }

    return 0;
}

