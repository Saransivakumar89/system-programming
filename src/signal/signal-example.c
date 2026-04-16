#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>

/*
 * When the ctrl + c , SIGINT is sent
 * handler starts exexcutes instead of the terminating the program
 * */

void sig_handler(int sig){
    //catches the CTRL + C 
    printf("\ncaught signal: %d\n", sig);
}


int main(void){
    
    signal(SIGINT, sig_handler);    // Handles the CTRL + C

    while(1){
        printf("running...\n");
        sleep(1);
    }

    return 0 ;
}

