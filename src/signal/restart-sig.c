#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<signal.h>
#include<errno.h>

void sig_handler(int sig){
    printf("signal:%d\n", sig);
}

int main(void){
    char buf[100];
    int fd = open("out.txt",O_RDWR | O_TRUNC ,0666);

    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    //Register the SIGINT for the handler
    if(sigaction(SIGINT, &sa ,NULL)==-1){
        perror("sigaction");
        return -1;
    }

    ssize_t n;

    while(n = read(fd,buf,100)==-1){
        if(errno==EINTR){
            printf("read interrupted\n");
            continue;
        }
        else{
            perror("read");
            break;
        }
    }

    return 0 ;
}

