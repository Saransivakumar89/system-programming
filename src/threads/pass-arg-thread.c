#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>

typedef struct {
    int id;
    int start;
    int end;
}data_t;

void *task(void *arg){
	
	data_t td = *(data_t *)arg;	
	printf("Thread %d :", td.id);
    for(int i = td.start ; i <= td.end ; i++){
        printf(" %d", i);
    }
    printf("\n");

	return NULL;
}

int main(){

    data_t data;
    data.id    = 1;
    data.start = 1;
    data.end   = 10;

    pthread_t t1;
    pthread_create(&t1, NULL, task, &data);
    
    pthread_join(t1, NULL);


    return 0;
}
