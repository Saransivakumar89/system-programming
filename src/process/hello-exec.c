#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>

/*
 * prints the PID of the e-file 
 * */

int main(void){
    
    printf("Hello-exec's PID : %d\n", getpid());

    return 0 ;
}

