#include<stdio.h>
#include<unistd.h>

int main(void){
    
    void * current = sbrk(0);

    printf("current : %p\n", current);

    if(brk(current + 100)==0){
        printf("Increased\n");
    }

    printf("New: %p\n", sbrk(0));

    return 0 ;
}

