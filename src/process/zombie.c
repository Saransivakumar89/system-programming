#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>

/*
 * Zombie process demo using fork()
 *
 * Child process exits immediately and becomes a zombie.
 * Parent sleeps for 10 seconds, then calls wait()
 * to remove the zombie process.
 */

int main(void){
    
    pid_t pid = fork();

    if(pid < 0){
        //fork failed
        perror("fork failed");
        return -1;
    }
    else if(pid == 0){
        //child process
        printf("child process | PID: %d PPID :%d\n", getpid(), getppid());
        exit(0);        // child process exits immediately
    }
    else if(pid > 0){
        // parent process
        sleep(1);
        printf("parent process (sleeping) | PID :%d\n", getpid());
        
        sleep(10);	//zombie visible here
        wait(NULL);	//reaps the child , clears the zombie
	
	printf("Parent : child reaped\n");
    }

    return 0 ;
}

