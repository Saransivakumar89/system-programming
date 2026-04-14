#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>
#define N 5

/* Create multiple child processes, store their PIDs, and reap them using waitpid in order */

int main(void){
    
    pid_t pid[N];

    for(int i = 0; i < N ; i++){
        pid[i] = fork();

        if(pid[i] < 0){
            // fork failed
            perror("fork failed");
            return -1;
        }
        else if(pid[i] == 0){
            //child process
            printf("child %d created | PID :  %d\n", i+1, getpid());
            
            sleep(1+i);  // simulating the work
            exit(0);
        }
        
    }

    while(1){
	// parent waits for the child and reaps them (Non-blocking)
        pid_t w_pid = waitpid(-1, NULL, WNOHANG);

        if(w_pid > 0){
            sleep(1);
            printf("child reaped PID :%d\n", w_pid);
        }
        else if(w_pid == 0){
            sleep(1);
            printf("child running...\n");
        }
        else {
            break;
        }    
    }

    printf("All children safely reaped\n");

    return 0 ;
}

