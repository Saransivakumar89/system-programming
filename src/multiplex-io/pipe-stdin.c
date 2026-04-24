#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>

int main(void) {
    fd_set readfds;
    int fd[2];
    char buff[100];

    if (pipe(fd) < 0) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        close(fd[0]);

        while (1) {
            const char *msg = "Message from child\n";
            write(fd[1], msg, strlen(msg));
            sleep(3);
        }
    }


    close(fd[1]);

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(STDIN_FILENO, &readfds);
        FD_SET(fd[0], &readfds);

        int maxfd = fd[0] ;

        printf("waiting for stdin or pipe...\n");

        int ret = select(maxfd + 1, &readfds, NULL, NULL, NULL);
        if (ret < 0) {
            perror("select");
            exit(1);
        }

        if (FD_ISSET(STDIN_FILENO, &readfds)) {
            ssize_t n = read(STDIN_FILENO, buff, sizeof(buff));
         
                write(STDOUT_FILENO, "STDIN: ", 7);
                write(STDOUT_FILENO, buff, n);
            
        }

        if (FD_ISSET(fd[0], &readfds)) {
            ssize_t n = read(fd[0], buff, sizeof(buff));
            
                write(STDOUT_FILENO, "PIPE: ", 6);
                write(STDOUT_FILENO, buff, n);
         }
        }

    return 0;
}
