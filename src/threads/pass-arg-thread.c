#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

void *task(void *arg){
	
	int id = *(int *)arg;	
	printf("Thread 1 passed : %d\n", id);
	return NULL;
}

int main(void){
    pthread_t t1 ;
    
    int val = 5;
    
    pthread_create(&t1, NULL, task, &val);
    
    pthread_join(t1, NULL);


    return 0;
}
