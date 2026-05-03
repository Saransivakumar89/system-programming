#include<stdio.h>
#include<pthread.h>

void *task_A(void * arg){
    printf("Thread 1 : A\n");
    return NULL;
}

void * task_B(void * arg){
    printf("Thread 2 : B\n");
    return NULL;
}

int main(void){
    
    pthread_t t1,t2;

    pthread_create(&t1, NULL, task_A, NULL);
    pthread_create(&t2, NULL, task_B, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0 ;
}

