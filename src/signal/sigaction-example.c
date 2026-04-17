#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<fcntl.h>
#include<setjmp.h>

sigjmp_buf env;

void sig_handler(int sig){  //Custom handler
    
    if(sig == SIGINT){
        printf("\nCaught SIGINT (ctrl+c)\n");
    }else if(sig == SIGTERM){
        printf("\nCaught SIGTERM\n");
    }else if(sig == SIGFPE){
        printf("\nCaught SIGFPE\n");
        siglongjmp(env,1);          //jumpout safely
    }

}

int main(void){
    
    struct sigaction sa;
    //Assigns handler
    sa.sa_handler = sig_handler;

    //No signals blocked during handler execution
    sigemptyset(&sa.sa_mask);
    
    sa.sa_flags = 0 ; //Flags - Default
    
    //Register handler for SIGINT
    if(sigaction(SIGINT,&sa, NULL)==-1){
        perror("sigaction");
        return -1;
    }
    
    //Register handler for SIGTERM
    if(sigaction(SIGTERM,&sa,NULL)==-1){
        perror("sigaction");
        return -1;
    }

    //Register handler for SIGFPE
    if(sigaction(SIGFPE,&sa,NULL)==-1){
        perror("sigaction");
        return -1;
    }
    

    sleep(1);

    if(sigsetjmp(env,1)==0){
        int a = 10 , b = 0 ;
        a = a / b;          //Fault occurs
    }
          
    printf("\nPress ctrl + c or send TERM to %d\n", getpid());

    while(1){
        sleep(1);
    }

    return 0 ;
}

