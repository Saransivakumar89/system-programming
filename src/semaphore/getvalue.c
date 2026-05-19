#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void *worker(void *arg)
{
    int val;

    /* Acquire semaphore */
    sem_wait(&sem);

    sem_getvalue(&sem, &val);
    printf("Entered critical section : %d\n", 
            val);

    sleep(3);

    /* Release semaphore */
    sem_post(&sem);

    sem_getvalue(&sem, &val);
    printf("Exited critical section : %d\n", 
            val);

    pthread_exit(NULL);
}

int main(void)
{
    pthread_t t1, t2;

    /* Initialize semaphore with value 1 */
    sem_init(&sem, 0, 1);

    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem);

    return 0;
}
