#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<signal.h>

int counter = 1;

void sig_handler(int sig){
    printf("\ncaught signal : %d\n", sig);
    counter++;
}

int main(void){
    
    signal(SIGINT, sig_handler);

    for(int i = 0 ; i < 10 ; i++){
        printf("%d\n", counter++);
        sleep(1);
    }

    return 0 ;
}

