#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

pthread_mutex_t lock ;
pthread_cond_t cond;
int ready = 0 ;

void * worker(void * arg)
{
    int id = *(int *)arg;
    pthread_mutex_lock(&lock);
    
    while(!ready){
        pthread_cond_wait(&cond, &lock);
    }

    printf("Received the broadcast signal from %d...\n", id);
    

    pthread_mutex_unlock(&lock);

    pthread_exit(NULL);
}

int main(void){
    
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&t1, NULL, worker, &id1);
   pthread_create(&t2, NULL, worker, &id2);
    
   // pthread_mutex_lock(&lock);
    sleep(2);
    ready = 1;
    pthread_cond_broadcast(&cond);
   // pthread_mutex_unlock(&lock);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&lock);

    return 0 ;
}

