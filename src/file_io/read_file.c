#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

/*
 *  Reads the data from the file and prints the output on the terminal 
 *  0 - stdin
 *  1 - stdout
 *  2 - stderr
 */

int main(void){
    
    char buf[100];
    int fd = open("hello.txt", O_RDWR | O_CREAT, 0644);

    if(fd == -1){
        // file creation failed
        perror("open");
        return -1;
    }

    ssize_t bytes_read;
    // read the data from the file and prints it
    while((bytes_read = read(fd, buf, sizeof(buf))) > 0){
        write(STDOUT_FILENO , buf, bytes_read);
    }

    close(fd);

    return 0 ;
}

