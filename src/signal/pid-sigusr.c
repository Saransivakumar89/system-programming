#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<signal.h>

/*
 *  Program receives the signal (SIGUSR1) from the another program
 */

void sig_handler(int sig){ //Custom Handler
    printf("signal received from another program\n");

}


int main(void){

    char * args[] = {NULL};
    
    pid_t pid = getpid();

    struct sigaction sa;

    sa.sa_handler = sig_handler;    

    sigemptyset(&sa.sa_mask);   //Clears the mask, No signals blocked during handler execution

    sa.sa_flags = 0;    //Default Behaviour

    if(sigaction(SIGUSR1,&sa, NULL)==-1){
        perror("sigaction");
        return -1;
    }
    
    execvp("./pid-b",args);

    while(1){
        sleep(1);
    }

    return 0 ;
}

