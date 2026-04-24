#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

int main(void){

    int fd = open("output.txt", O_RDWR | O_CREAT | O_TRUNC , 0666);

    if(fd < 0){
        perror("open");
        return -1;
    }

    dup2(fd,STDOUT_FILENO);
    
    close(fd);

    execl("/bin/ls", "ls", "-l",NULL);

    return 0 ;
}

