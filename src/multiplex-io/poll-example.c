#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<poll.h>

int main(void){
    
    struct pollfd fds[2];

    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    //fds[1].fd = STDOUT_FILENO;
    //fds[1].events= POLLOUT;

    printf("waiting for the input (5secs)...\n");

    int ret = poll(fds,1,5000);

    if(ret == 0){
        printf("timeout\n");
    }
    else if(ret > 0){
        if(fds[0].revents & POLLIN){
            printf("data available...\n");
        }
        //else if(fds[1].revents & POLLOUT){
         //   printf("stdout...\n");
        //}
    }
    else {
        perror("poll");
    }

    return 0 ;
}

