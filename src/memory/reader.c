#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/mman.h>
#include<fcntl.h>


#define SIZE 4096

int main(void){
    
    char * name = "/my_shm";
    
    int fd = shm_open(name,O_RDONLY , 0666);

    ftruncate(fd,SIZE);

    char *ptr = mmap(0,SIZE,PROT_READ,MAP_SHARED,fd,0);

    if(ptr == MAP_FAILED){
        close(fd);
        perror("mmap");
        return -1;
    }

    printf("Data : %s\n", ptr);

    munmap(ptr,SIZE);

    close(fd);
    
    shm_unlink(name);

    return 0 ;
}

