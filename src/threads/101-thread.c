#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *task_A(void * arg){
    printf("Thread 1 : A\n");
    int *x = malloc(sizeof(int));
    *x = 122;
    pthread_exit(x);
}

void * task_B(void * arg){
    printf("Thread 2 : B\n");
    int * y = malloc(sizeof(int));
    *y = 21;
    pthread_exit(y);
}

int main(void){
    
    pthread_t t1,t2;

    void *x;
    void *y;

    pthread_create(&t1, NULL, task_A, NULL);
    pthread_create(&t2, NULL, task_B, NULL);
    
    pthread_join(t1, &x);
    pthread_join(t2, &y);

    printf("returned value t1 : %d, t2 : %d\n", *(int*)x, *(int*)y);

    return 0 ;
}

