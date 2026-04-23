#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

#define FIFO "/tmp/fifo"

int main(void){
    int arr[10];
    int val = 0;
    if(mkfifo(FIFO,0666)==-1){
        perror("mkfifo");
        return -1;
    }

    int fd = open(FIFO,O_WRONLY);

    if(fd < 0){
        perror("open");
        return -1; 
    }

    for(int i = 0 ; i < 10; i++){
        val = arr[i] = i+1;
        write(fd,&val,sizeof(val));
    }
    
    printf("messgae sent\n");
    close(fd);


    return 0 ;
}

