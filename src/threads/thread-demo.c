#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

/* 
 * output-interleave will happen because there is no synchronization
 */

void *task(void * arg){
    while(1){
        printf("Thread-1 running...\n");
        sleep(2);   
    }
    return NULL;
}

void *new_task(void *arg){
    while(1){
        printf("Thread-2 running...\n");
        sleep(2);
    }
    return NULL;
}

int main(void){
    
    pthread_t t1, t2;

    pthread_create(&t1,NULL,task,NULL);

    pthread_create(&t2,NULL,new_task,NULL);

    pthread_join(t1,NULL);
    
    pthread_join(t2,NULL);

    return 0 ;
}

