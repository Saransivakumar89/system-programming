#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<fcntl.h>
#include<setjmp.h>
#include<sys/wait.h>

sigjmp_buf env;

void sig_handler(int sig){  //Custom handler
    
    if(sig == SIGINT){
        printf("\nCaught SIGINT (ctrl+c)");
    }else if(sig == SIGTERM){
        printf("\nCaught SIGTERM");
    }else if(sig == SIGFPE){
        printf("\nCaught SIGFPE");
        siglongjmp(env,1);          //jumpout safely
    }else if(sig == SIGCHLD){
        printf("\nCaught SIGCHLD");
    }else if(sig == SIGALRM){
        printf("\nCaught SIGALRM");
    }

}

int main(void){
    
    struct sigaction sa;
    //Assigns handler
    sa.sa_handler = sig_handler;

    //No signals blocked during handler execution
    sigemptyset(&sa.sa_mask);
    
    sa.sa_flags = 0;//SA_RESTART; //Flags - Default
    
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
    
    //Register handler for SIGCHLD
    if(sigaction(SIGCHLD, &sa, NULL)==-1){
        perror("sigaction");
        return -1;
    }

    //REgister handler for SIGALRM
    if(sigaction(SIGALRM,&sa,NULL)==-1){
        perror("sigaction");
        return -1;
    }
    

    sleep(1);

    if(sigsetjmp(env,1)==0){
        int a = 10 , b = 0 ;
        a = a / b;          //Fault occurs
    }
          
    sleep(1);
    fflush(stdout);
    pid_t pid = fork();

    if(pid < 0){
        // fork failed
        perror("fork failed");
        return -1;
    }
    else if(pid == 0){ //child process
        exit(0);
    }
    else if(pid > 0){   //parent process
        wait(NULL);
    }

    sleep(1);

    alarm(2);   //timer for 2 secs
    
    sleep(1);

    printf("\nPress ctrl + c or send TERM to %d\n", getpid());

    

    while(1){
        sleep(1);
    }

    return 0 ;
}

