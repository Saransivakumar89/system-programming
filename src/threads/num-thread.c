#include<stdio.h>
#include<pthread.h>

void * task(void * arg){

    for(int i = 0 ; i < 5 ; i++){
        printf("%d ", i+1);
    }

    printf("\n");

    return NULL;
}


int main(void){
    
    pthread_t t1;

    pthread_create(&t1, NULL, task, NULL);

    pthread_join(t1, NULL);

    return 0 ;
}

