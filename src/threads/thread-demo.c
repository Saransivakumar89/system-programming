#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void *task(void * arg){
    printf("Thread\n");
}

int main(void){
    
    pthread_t t1;

    pthread_create(&t1,NULL,task,NULL);

    pthread_join(t1,NULL);

    return 0 ;
}

