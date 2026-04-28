#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void *task(void * arg){
    while(1){
        printf("Thread running...\n");
        sleep(2);   
    }
}

int main(void){
    
    pthread_t t1;

    pthread_create(&t1,NULL,task,NULL);

    pthread_join(t1,NULL);

    return 0 ;
}

