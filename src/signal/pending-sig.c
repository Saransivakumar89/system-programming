#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<fcntl.h>
#include<sys/wait.h>

int main(void){
    
    sigset_t set, pending;

    sigemptyset(&set);
    sigemptyset(&pending);
    
    sigaddset(&set, SIGINT);
    sigprocmask(SIG_BLOCK, &set, NULL);

    printf("press ctrl+C...\n");
    sleep(5);
    sigprocmask(SIG_BLOCK, &set, NULL);

    sigpending(&pending);   //check the pending signal
    
    if(sigismember(&pending,SIGINT)){
        printf("SIGINT Pending\n");
    }
    else {
        printf("SIGINT not pending\n");
    }
    
    //unblock
    sigprocmask(SIG_UNBLOCK, &set, NULL);
    
    while(1){
        printf("...\n");
    	pause();
    }
    

    return 0 ;
}

