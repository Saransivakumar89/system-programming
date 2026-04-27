#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/mman.h>
#include<fcntl.h>


#define SIZE 4096

int main(void){
    
    char * name = "/my_shm";
    
    int fd = shm_open(name, O_CREAT | O_RDWR , 0666);

    ftruncate(fd,SIZE);

    char *ptr = mmap(0,SIZE,PROT_WRITE,MAP_SHARED,fd,0);

    if(ptr == MAP_FAILED){
        close(fd);
        perror("mmap");
        return -1;
    }

    sprintf(ptr,"Hello from writer\n");
    
    printf("Data written successfully\n");

    munmap(ptr,SIZE);

    close(fd);

    return 0 ;
}

