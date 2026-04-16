#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<string.h>

/*
 *
 * */

int main(void){
    
    char *buf = "writing to the file...\n";

    int fd = open("hello.txt", O_WRONLY | O_CREAT | O_TRUNC , 0644);

    if(fd == -1){
        // file open failed
        perror("open");
        return -1;
    }

    ssize_t bytes_written = write(fd, buf, strlen(buf));

    if(bytes_written == -1){
        perror("error write");
        close(fd);
        return -1;
    }
    
    printf("successfully wrote %ld bytes\n", bytes_written);
    close(fd);

    return 0 ;
}

