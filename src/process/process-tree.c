#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>

/* Process Tree Visualization using fork()
*  simple 1-level process tree:Parent -> Child1, Child2, Child3
*  Each child process prints its PID and PPID
*/



int main(void){
    
    printf("Parent | PID - %d\n", getpid());

    pid_t pid ;

    for(int i = 0 ; i < 3 ; i++){
        pid = fork();

        if(pid < 0){
            // fork failed
            perror("fork()");
            return -1;       
        }
        else if(pid == 0){
            // child process
            
            if(i == 0){
                printf("|--child1 | PID : %d PPID : %d\n", getpid(), getppid());   
            }
            else if(i == 1){
                printf("|--child2 | PID : %d PPID : %d\n", getpid(), getppid());
            }
            else if(i == 2){ 
                printf("|--child3 | PID : %d PPID : %d\n", getpid(), getppid());
            }    
        
    
        fflush(stdout);
        exit(0);
    	}
    }
    // parent waits for all children
    for(int i = 0 ; i < 3 ;i++){
        wait(NULL);
    }

    return 0 ;
}

