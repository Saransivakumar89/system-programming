#define _GNU_SOURCE

#include<stdio.h>
#include<sched.h>
#include<pthread.h>
#include<unistd.h>

void * worker (void * arg){
    
    int id = *(int *)arg;

    for(int i = 0 ; i < 5 ;i++){
        printf("Thread %d - %d\n", id, i);
        sched_yield();

        sleep(1);
    }
    
    pthread_exit(NULL);
}


int main(void){
    
    pthread_t t1, t2;

    int a = 1, b = 2;

    pthread_create(&t1, NULL, worker, &a);
    pthread_create(&t2, NULL, worker, &b);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    

    return 0 ;
}

