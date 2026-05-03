#include<stdio.h>
#include<pthread.h>

typedef struct{
    int a;
    int b;
}data_t;

void * task (void * arg){
    data_t x = *(data_t*)arg;
    
    int sum = x.a + x.b;

    printf("sum : %d\n", sum);

    return NULL;
}


int main(void){
    
    pthread_t t1;
        
    data_t data ;

    data.a = 12;
    data.b = 34;

    pthread_create(&t1, NULL, task, &data);

    pthread_join(t1, NULL);

    return 0 ;
}

