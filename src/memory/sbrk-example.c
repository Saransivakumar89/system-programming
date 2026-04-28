#include<stdio.h>
#include<unistd.h>

int main(void){
    
    void * p1, *p2 ;

    p1 = sbrk(0);

    printf("Current break : %p\n", p1);

    sbrk(100);
    
    p2 = sbrk(0);

    printf("After increasing bytes : %p\n", p2);
    
    printf("Diff: %ld\n", (char *)p2 - (char *)p1);

    return 0 ;
}

