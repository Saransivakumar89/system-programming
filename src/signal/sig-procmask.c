#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>
#include<sys/wait.h>

int main(void){
    
    pid_t pid = getpid();
    printf("PID: %d\n", pid);

    sigset_t set, new_set;

    sigemptyset(&set);  //Clear the mask/set so the no signals blocked during sig handler exection
    sigemptyset(&new_set);

    sigaddset(&set,SIGINT); //add the SIGINT to the set
   
    sigprocmask(SIG_BLOCK, &set , NULL); // block the set 
    
    printf("SIGINT blocked here for 5 secs\n");

    sleep(5);
    
    //sigemptyset(&set);

    //sigaddset(&set,SIGTERM);
    
   // printf("SIGTERM is blocked\n");

    printf("\nSIGINT unblocked\n"); 
    sigprocmask(SIG_SETMASK, &new_set, NULL);   //unblock the set 
   
#ifdef NEWMASK    
     sleep(20);

    sigprocmask(SIG_UNBLOCK, &set, NULL);

    printf("SIGTERM unblocked\n");
#endif
    return 0 ;
}

