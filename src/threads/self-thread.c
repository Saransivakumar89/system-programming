#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/time.h>

void print_time(void){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("%ld.%06ld -- ", tv.tv_sec, tv.tv_usec);
    fflush(stdout);
}


void * task(void * arg){
    int id = *(int *)arg;
    for(int i = 0 ; i < 5 ; i++){
        print_time();
        printf("Thread %d ID : %lu\n",id,(unsigned long)pthread_self());
        usleep(1000);
    }
    return NULL;    
}

int main(void){
    
    pthread_t t1,t2;
    int id1 = 1 , id2 = 2;

    pthread_create(&t1, NULL, task, &id1);
    pthread_create(&t2, NULL, task, &id2);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);


    printf("Main Thread ID: %lu\n",(unsigned long)pthread_self());

    return 0 ;
}

