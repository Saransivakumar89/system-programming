#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>

int main(void){
   
    pid_t pid = fork(); 

    if(pid < 0){
        //fork failed
        perror("fork()");
        return -1;
    }
    else if(pid == 0){
        // child process
        printf("child | PID : %d PPID :%d\n", getpid(), getppid());

        pid_t gc_id = fork();
    
        if(gc_id < 0){
            // fork failed
            perror("fork failed");
            return -1;
        }
        else if(gc_id == 0){
            //Grandchild process
            printf("Grand Child | PID : %d PPID :%d\n", getpid(),getppid());
        }
        //child waits for grandchild
        wait(NULL);
        exit(0);   
    }
    else if(pid > 0)
    {   //Parent process
        waitpid(pid, NULL, 0);
        printf("Parent | PID : %d PPID : %d\n", getpid(), getppid());
    }

    return 0 ;
}

