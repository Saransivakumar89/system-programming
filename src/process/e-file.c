#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>

/*
 * execvp() - replaces the current process with the new process image
 * ./hello-exec -> path to be executable
 *  returns the error
 * */

int main(void){
    
    char *args[] = {NULL};

    pid_t pid = getpid();   // PID of the calling process/current program

    printf("e-file's PID : %d\n", pid);     
    
    execvp("./hello-exec", args);   

    printf("exec failed\n");    //On success never returns

    return 0 ;
}

