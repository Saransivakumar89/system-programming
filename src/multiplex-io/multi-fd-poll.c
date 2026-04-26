#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<poll.h>

int main(void){
    
    int fd[2];

    pipe(fd);

    struct pollfd fds[2];
    
    //stdin
    
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    //pipe
    
    fds[1].fd = fd[0];
    fds[1].events = POLLIN;
    
    char *msg = "Hello from pipe\n";
    write(fd[1],msg,strlen(msg));
    

    printf("waiting for the data...\n");
    int ret = poll(fds,2,5000);
    
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
            read(fd[0],buff,sizeof(buff));
            printf("pipe : %s\n",buff);
        }
    }
    else{
        perror("poll");
    }



    return 0 ;
}

