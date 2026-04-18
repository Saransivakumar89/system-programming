#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>

int main(void){
    
    pid_t pid = getpid();
    
    printf("sending signal in 3 secs to pid : %d\n", pid);

    sleep(3);

    //kill(pid,SIGUSR1);
    
    raise(SIGUSR1);

    return 0 ;
}

