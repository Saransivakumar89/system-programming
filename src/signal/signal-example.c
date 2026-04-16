#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

/*
 * When the ctrl + c , SIGINT is sent
 * handler starts exexcutes instead of the terminating the program
 * 
 * custom handler catches the SIGINT
 * SIG_IGN ignores the SIGINT
 * SIG_DFL terminates the SIGINT
 * */
int sig_count = 0;
void sig_handler(int sig){
    //catches the CTRL + C 
    sig_count++;
    printf("\ncaught signal: %d...pressed %d times\n", sig, sig_count);

    if(sig_count >=3)
    {
        exit(0);
    }
}


int main(void){
    
    printf("Custom handler(5 secs)\n");
    signal(SIGINT, sig_handler);    // Handles the CTRL + C
    sleep(5);
    sig_count = 0;

    printf("\nignores the SIGINT (5 secs)\n");
    signal(SIGINT, SIG_IGN);    // ignores the CTRL + C
    sleep(5); 

    printf("\nDefault handler (5 secs)\n");
    signal(SIGINT, SIG_DFL);    // Default Handler for CTRL + C(terminates)
    sleep(5);

    sig_count = 0;
    printf("\nCustom handler...Press 3 times to terminate\n");
    signal(SIGINT, sig_handler);
    

    while(1){
        printf("running...\n");
        sleep(1);
    }

    return 0 ;
}

