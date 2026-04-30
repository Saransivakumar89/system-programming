#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

/*
 *  Since it is a shared resources race-condition will occur
 * */
 
int x = 0;

void * counter(void *arg){
    for(int i = 0 ; i < 1000000 ; i++){
        x++;
    }
    return NULL;
}


int main(void){
     
    pthread_t t1, t2;

   if(pthread_create(&t1,NULL,counter,NULL)!=0){
     //thread-creation
     perror("t1");
     return -1;
    }


   if(pthread_create(&t2,NULL,counter,NULL)!=0){
     //thread-creation
     perror("t2");
     return -1;
    }

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    printf("value : %d\n", x);

    return 0 ;
}

