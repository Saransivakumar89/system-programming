#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<poll.h>

int main(void){
    
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(1);
    }

    struct pollfd fds[2];
    
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    fds[1].fd = fd[0];
    fds[1].events = POLLIN;

    pid_t pid = fork();

    if(pid == 0){
        // child: writer
        close(fd[0]);

        sleep(3);
        char *msg = "Hello from pipe\n";
        write(fd[1], msg, strlen(msg));

        close(fd[1]);
        exit(0);
    }
    else if (pid > 0){
        // parent: reader
        close(fd[1]);
    }
    else {
        perror("fork");
        exit(1);
    }

    printf("waiting for the data...\n");
    int ret = poll(fds, 2, 5000);
    
    if(ret == 0){
        printf("timeout\n");
    }
    else if(ret > 0){
        
        if(fds[0].revents & POLLIN){
            printf("STDIN: data available\n");
        }

        if(fds[1].revents & POLLIN){
            printf("PIPE : data ready\n");

            char buff[40];
            int n = read(fd[0], buff, sizeof(buff)-1);
            if(n > 0){
                buff[n] = '\0';
                printf("pipe : %s\n", buff);
            }
        }
    }
    else{
        perror("poll");
    }

    close(fd[0]);
    return 0;
}
