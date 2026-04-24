#include<stdio.h>
#include<unistd.h>
#include<sys/select.h>

int main(void){
    
    fd_set readfds;

    int maxfd;
    char buff[100];

    while(1){
        FD_ZERO(&readfds);

        FD_SET(0,&readfds);

        maxfd = 0;

        printf("waiting for input...\n");

        int ret = select(maxfd+1,&readfds,NULL,NULL,NULL);

        if(ret < 0){
            perror("select");
            return -1;
        }

        if(FD_ISSET(0,&readfds)){
            ssize_t n = read(0,buff,sizeof(buff));
            write(1,buff,n);
        }
    }

    return 0 ;
}

