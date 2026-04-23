#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>

int main(void){
    
    int fd = open("dup-file.txt", O_CREAT | O_RDWR | O_TRUNC, 0666);

    if(fd < 0){
        perror("open");
        return -1;
    }

    int copy_fd;
    
    copy_fd = dup(fd);

    printf("Original FD : %d\n", fd);
    printf("Duplicate FD : %d\n", copy_fd);
    
    char * buff = "Hello";

    write(fd,buff, strlen(buff)+1);

    char *cp_buff = "World\n";
    
    write(copy_fd, cp_buff, strlen(cp_buff));

    close(copy_fd);
    close(fd);

    return 0 ;
}

