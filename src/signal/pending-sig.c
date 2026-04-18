#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<fcntl.h>
#include<sys/wait.h>

int main(void){
    
    sigset_t set;

    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigprocmask(SIG_BLOCK, &set, NULL);

    printf("press ctrl+C\n");
    sleep(5);
    sigprocmask(SIG_BLOCK, &set, NULL);

    sigpending(&set);   //check the pending signal
    
    if(sigismember(&set,SIGINT)){
        printf("SIGINT is pending\n");
    }
    else {
        printf("SIGINT is not pending\n");
    }


    return 0 ;
}

