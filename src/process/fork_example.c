#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>

/*
 * Simple demo of process creation using fork()
 * The Parent Creates a child, both prints their PID 
 * and the parent waits/sleeps for the 2 secs, to prevent zombie
 */

int main(void){
    
    pid_t pid = fork();

    if(pid < 0){
        //fork failed
        perror("fork()");
        return -1;
    } 
    else if(pid == 0){
        //Child process
        printf("child process | PID : %d PPID : %d\n", getpid(), getppid());
    }
    else if(pid > 0){
        //Parent process
        sleep(2); // parent sleeps for 2 seconds - to prevent zombie
        printf("parent process | PID : %d Child's PPID : %d\n", getpid(), pid);
    }


    
    return 0 ;
}

