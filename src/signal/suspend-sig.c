#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>

volatile sig_atomic_t flag = 0; 

void sig_handler(int sig){//custom handler
	flag = 1;   //updates the flags
}

int main(void){
    
    sigset_t set, wait_set;
    
    signal(SIGINT, sig_handler);    	
   	
    sigemptyset(&set);      
    sigaddset(&set, SIGINT);    //clears and add the SIGINT to set/mask

    sigprocmask(SIG_BLOCK, &set, NULL); //blocks the SIGINT
    printf("SIGINT - BLOCKED\n");

    sleep(5);

    printf("\nwaiting...\n");

    sigemptyset(&wait_set); 
    
    while(!flag){
        sigsuspend(&wait_set);  //waits 
    }
    
    printf("Exit safely\n");
    
    return 0 ;
}

