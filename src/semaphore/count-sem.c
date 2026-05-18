#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

sem_t sem;

void *worker(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&sem);

    printf("Thread %d Entered Critical Section\n", id);

    sleep(5);

    printf("Thread %d Leaving Critical Section\n", id);

    sem_post(&sem);

    pthread_exit(NULL);
}

int main(void)
{
    pthread_t t[N];
    int ids[N];

    sem_init(&sem, 0, 3);

    for (int i = 0; i < N; i++)
    {
        ids[i] = i + 1;

        pthread_create(&t[i], NULL, worker, &ids[i]);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(t[i], NULL);
    }

    sem_destroy(&sem);

    return 0;
}
