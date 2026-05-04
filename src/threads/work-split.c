#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define N 5

typedef struct {
    int id;
    int start;
    int end;
}data_t;

void * worker(void *arg){
    
    data_t *t_d = (data_t*)arg;
    
    printf("[Thread %d] :", t_d->id);
    for(int i = t_d->start ; i <= t_d->end ; i++){
        printf(" %d", i);
    }
    printf("\n");

    return NULL;
}

int main(void){
    
    data_t data[N];
    int total = 20;
    int wrk_per_thread = total / N;
    

    pthread_t t[N];
    
    for(int i = 0 ; i < N ;i++){
        data[i].id = i+1; 
        data[i].start = i * wrk_per_thread ;
        data[i].end   = (i+1) * wrk_per_thread -1;
        
        if(i == N - 1){
            data[i].end = total -1;
        }

        pthread_create(&t[i], NULL, worker, &data[i]);
    }

    for(int i = 0 ; i < N ;i++){
        pthread_join(t[i], NULL);
    }

    return 0 ;
}

