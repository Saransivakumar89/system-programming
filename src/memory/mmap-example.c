#include<stdio.h>
#include<sys/mman.h>

int main(void){
    
    int * ptr = mmap(NULL, 4, PROT_READ | PROT_WRITE , MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if(ptr == MAP_FAILED){
        perror("mmap");
        return -1;
    }

    ptr[0] = 4;

    printf("*ptr = %d\n", *ptr);

    if(munmap(ptr,4)==-1){
        perror("munmap");
        return -1;
    }

    return 0 ;
}

