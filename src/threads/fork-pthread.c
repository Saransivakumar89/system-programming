#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/wait.h>

pthread_mutex_t lock;

void prepare(){
    printf("Prepare\n");
    pthread_mutex_lock(&lock);
}

void child(){
    printf("child\n");
    pthread_mutex_unlock(&lock);
}


void parent(){
    printf("parent\n");
    pthread_mutex_unlock(&lock);
}

int main(void){
    
    pthread_mutex_init(&lock, NULL);
    
    pthread_atfork(prepare, parent , child);

    pid_t pid = fork();

    if(pid == 0){
        printf("inside child process\n");
    }else{
        wait(NULL);
        printf("inside parent process\n");
    }

    pthread_mutex_destroy(&lock);

    return 0 ;
}

