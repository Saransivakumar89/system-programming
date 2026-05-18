#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>

sem_t sem;

void * worker(void * arg){
    
    sem_wait(&sem);

    printf("Entered Critical Section\n");

    sleep(3);

    printf("Exiting Critical Section\n");

    sem_post(&sem);
    pthread_exit(NULL);
}


int main(void){
    
    pthread_t t1, t2;
    
    sem_init(&sem, 0, 1);

    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);
   
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem);

    return 0 ;
}

