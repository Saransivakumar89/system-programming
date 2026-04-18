#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/wait.h>

/*
 * Reaps the zombie process without wait/waitpid
 * */


void sig_handler(int sig){ //custom handler
    printf("Child Exited\n");
}


int main(void){

    struct sigaction sa;

    sa.sa_handler = sig_handler;

    sigemptyset(&sa.sa_mask);       //no signal blocked during handler

    sa.sa_flags = SA_NOCLDWAIT;     //Automatically reaps the child
    
    //Register the SIGCHLD 
    if(sigaction(SIGCHLD, &sa, NULL)==-1){
        perror("sigaction");
        return -1;
    }
    
    pid_t pid = fork();
    if(pid < 0){
        // fork failed
        perror("fork");
        return -1;
    }
    else if(pid == 0){
        //child
        exit(0);
    }
    else if(pid > 0)
    {
        printf("parent waiting\n");
        pause();        //waits for the signal to arrive
    }


    return 0 ;
}

