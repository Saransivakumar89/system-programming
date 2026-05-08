#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t lock;

void * worker(void * arg){
    
    int id = *(int *)arg;

    if(pthread_mutex_trylock(&lock)==0){
        printf("Thread %d got locked\n", id);
        sleep(2);
        pthread_mutex_unlock(&lock);
    }else{
        printf("Thread %d couldn't locked\n", id);
    }
    
    pthread_exit(NULL);
}

int main(void){
    
    pthread_t t1, t2;
    int id1 = 1 , id2 = 2;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t1, NULL, worker, &id1);
    pthread_create(&t2, NULL, worker, &id2);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);



    return 0 ;
}

