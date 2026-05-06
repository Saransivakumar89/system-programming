#include<stdio.h>
#include<pthread.h>

pthread_mutex_t lock;
pthread_cond_t cond;
int turn = 0;

void * thread_A(void * arg){
    pthread_mutex_lock(&lock);
    
    while(turn != 0){
        pthread_cond_wait(&cond, &lock);
    }
    printf("A\n");
    
    turn = 1;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
    return NULL;
}


void * thread_B(void * arg){

    pthread_mutex_lock(&lock);

    while(turn != 1)
    {
        pthread_cond_wait(&cond, &lock);
    }

    printf("B\n");
    turn = 0;

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
 
    return NULL;
}

int main(void){
    
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&t1, NULL, thread_A, NULL);
    pthread_create(&t2, NULL, thread_B, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&lock);

    return 0 ;
}

