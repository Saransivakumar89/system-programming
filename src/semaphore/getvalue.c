#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

int main(void){
    
    sem_t sem;

    int val;

    sem_init(&sem, 0 , 3);

    sem_wait(&sem);
    
    sem_getvalue(&sem, &val);

    printf("After sem wait : %d\n", val);

    sleep(2);

    sem_post(&sem);

    sem_getvalue(&sem,&val);
    
    printf("After the sem post : %d\n", val);

    sem_destroy(&sem);

    return 0 ;
}

