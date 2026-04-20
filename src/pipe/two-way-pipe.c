#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<stdint.h>
#include<ctype.h>

/**
 *  child sends the message to parent 
 *  parent converts the message to Uppercase
 *  parent sends back to the child  
 */

int main(void){
    
    int fd1[2], fd2[2];
    
    pipe(fd1);  //parent writes to child
    pipe(fd2);  //child writes to parent

    pid_t pid = fork();

    if(pid < 0){
        perror("fork");
        return -1;
    }
    else if(pid == 0){
        //child process
        close(fd1[0]);  
        close(fd2[1]);

        char * msg = "Hello, kernel buffer";
        write(fd1[1], msg, strlen(msg)+1);
        
        char buff[100];
        read(fd2[0], buff, sizeof(buff));
        
        printf("child received : %s\n", buff);

        close(fd1[1]);
        close(fd2[0]);
    }
    else{
    //parent process
    close(fd1[1]);
    close(fd2[0]);

    char buff[100];
    
    read(fd1[0],buff,sizeof(buff));
    
    printf("parent received : %s\n", buff);

    for(uint8_t i = 0 ; buff[i];i++){
        buff[i] = toupper(buff[i]);
    }

    write(fd2[1], buff, strlen(buff)+1);


    close(fd1[0]);
    close(fd2[1]);
    }


    return 0 ;
}

