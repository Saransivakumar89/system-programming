#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>

/*
 * Orphan process demo using fork()
 *
 * Parent exits immediately, so the child becomes an orphan.
 * The child is adopted by init/systemd (PID 1) - In VM PID may vary.
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
        sleep(2);	// ensures the parent exits first
        printf("child process | PID: %d PPID :%d\n", getpid(), getppid());
    }
    else if(pid > 0){
        // parent process
        printf("parent process  | PID :%d\n", getpid());
        exit(0); //Parent exits immediately
    }

    return 0 ;
}

