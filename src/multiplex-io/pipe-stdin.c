#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>
#include <sys/time.h>   // FIX: needed for gettimeofday

int main(void) {
    fd_set readfds;
    int fd1[2], fd2[2];
    char buff[100];
    struct timeval tv, start, end;

    if (pipe(fd1) < 0 || pipe(fd2) < 0) {
        perror("pipe");
        exit(1);
    }

    // Child 1 
    if (fork() == 0) {
        close(fd1[0]);
        close(fd2[0]);
        close(fd2[1]);

        while (1) {
            const char *msg = "PING\n";
            write(fd1[1], msg, strlen(msg));
            sleep(3);
        }
    }

    // Child 2 
    if (fork() == 0) {
        close(fd2[0]);
        close(fd1[0]);
        close(fd1[1]);

        while (1) {
            const char *msg = "PONG\n";
            write(fd2[1], msg, strlen(msg));
            sleep(3);
        }
    }

    // Parent
    close(fd1[1]);
    close(fd2[1]);

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(fd1[0], &readfds);
        FD_SET(fd2[0], &readfds);

        int maxfd = fd1[0] > fd2[0] ? fd1[0] : fd2[0];
        if (STDIN_FILENO > maxfd)
            maxfd = STDIN_FILENO;

        tv.tv_sec = 5;
        tv.tv_usec = 0;

        printf("Waiting for input (pipes/stdin)...\n");

        gettimeofday(&start, NULL);

        int ret = select(maxfd + 1, &readfds, NULL, NULL, &tv);

        gettimeofday(&end, NULL);

        double elapsed =
            (end.tv_sec - start.tv_sec) +
            (end.tv_usec - start.tv_usec) / 1000000.0;

        printf("Elapsed time: %.3f seconds\n", elapsed); // FIX

        if (ret < 0) {
            perror("select");
            exit(1);
        }

        if (ret == 0) {
            printf("Timeout occurred\n");
            continue;
        }

        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            ssize_t n = read(STDIN_FILENO, buff, sizeof(buff));
            if (n > 0) {
                write(STDOUT_FILENO, "STDIN: ", 7);
                write(STDOUT_FILENO, buff, n);
            }
        }

        if (FD_ISSET(fd1[0], &readfds)) {
            ssize_t n = read(fd1[0], buff, sizeof(buff));
            if (n > 0) {
                write(STDOUT_FILENO, "C1: ", 4);
                write(STDOUT_FILENO, buff, n);
            }
        }

        if (FD_ISSET(fd2[0], &readfds)) {
            ssize_t n = read(fd2[0], buff, sizeof(buff));
            if (n > 0) {
                write(STDOUT_FILENO, "C2: ", 4);
                write(STDOUT_FILENO, buff, n);
            }
        }

        printf("\n");
    }

    return 0;
}
