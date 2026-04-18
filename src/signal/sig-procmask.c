#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/wait.h>

int main(void){
    
    sigset_t set;

    sigemptyset(&set);  //Clear the mask/set so the no signals blocked during sig handler exection

    sigaddset(&set,SIGINT); //add the SIGINT to the set
    
    sigprocmask(SIG_BLOCK, &set , NULL); // block the set 
    
    printf("SIGINT blocked here for 5 secs\n");

    sleep(5);

    printf("\nSIGINT unblocked...\n");

    sigprocmask(SIG_UNBLOCK, &set, NULL);   //unblock the set 



    return 0 ;
}

