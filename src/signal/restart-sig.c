#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

void sig_handler(int sig){
    write(STDOUT_FILENO, "SIGINT received\n", 16);
}

int main(void){
    char buf[100];
    int fd = open("out.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
    if(fd == -1){
        perror("open");
        return -1;
    }

    // Write something so we can read later
    const char *msg = "Hello, world!\n";
    write(fd, msg, strlen(msg));
    lseek(fd, 0, SEEK_SET); // reset file offset

    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if(sigaction(SIGINT, &sa, NULL) == -1){
        perror("sigaction");
        return -1;
    }

    ssize_t n;
    while((n = read(fd, buf, sizeof(buf))) != 0){
        if(n == -1){
            if(errno == EINTR){
                printf("read interrupted\n");
                continue;
            } else {
                perror("read");
                break;
            }
        }
        write(STDOUT_FILENO, buf, n);
    }

    close(fd);
    return 0;
}


