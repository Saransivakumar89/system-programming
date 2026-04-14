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
    
    int x = 10; 
    printf("x : %d\n", x);
    
    pid_t pid = fork();

    if(pid < 0){
        //fork failed
        perror("fork()");
        return -1;
    } 
    else if(pid == 0){
        //Child process

        x = 21;     // child modifies the x -> COW happens here   
        printf("child process | PID : %d PPID : %d\nchild modifies x : %d\n", getpid(), getppid(), x);
        sleep(2);
    }
    else if(pid > 0){
       //Parent process
       // sleep(2); // parent sleeps/waits for 2 seconds - to prevent zombie
        wait(NULL);
        printf("parent process | PID : %d Child's PPID : %d\nparent's x : %d\n", getpid(), pid, x);
    }


    
    return 0 ;
}

