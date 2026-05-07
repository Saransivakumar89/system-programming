#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>

void print_time(void){
    struct timespec ts;

    clock_gettime(CLOCK_REALTIME, &ts);
    printf("%ld.%09ld -- ", ts.tv_sec, ts.tv_nsec);
}

void * task(void *arg){
    int id = *(int*)arg;
    
    for(int i = 0 ; i < 100 ; i++){
        print_time();
        printf("Thread[%d]ID: %lu\n", id, (unsigned long)pthread_self());
         for(long j = 0; j < 50000000; j++); 
    }

    return NULL;
}


int main(void){
    
    pid_t pid = getpid();
    printf("PID  : %d\n", pid);
    printf("PPID : %d\n", getppid());
    sleep(2);
    pthread_t t1, t2, t3;

    int id1 = 1, id2 = 2 , id3 = 3;

    pthread_create(&t1, NULL, task, &id1);
    pthread_create(&t2, NULL, task, &id2);
    pthread_create(&t3, NULL, task, &id3);
   
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0 ;
}

