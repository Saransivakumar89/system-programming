#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

#define N 5

pthread_barrier_t barrier;

void * worker(void * arg){
    
    int id = *(int*)arg;
    
    printf("Thread {%d}  reached barrier\n", id);

    sleep(id);

    pthread_barrier_wait(&barrier);

    printf("Thread {%d} after barrier\n", id);

    pthread_exit(NULL);
}


int main(void){

    int ids[N];
    pthread_t t[N];

    pthread_barrier_init(&barrier, NULL, N);    
    
    for(int i = 0 ; i < N ;i++){
        ids[i] = i+1; 
        pthread_create(&t[i], NULL, worker, &ids[i]);
    }

    
    for(int i = 0 ; i < N ;i++){
        pthread_join(t[i], NULL);
    }

    pthread_barrier_destroy(&barrier);

    return 0 ;
}

