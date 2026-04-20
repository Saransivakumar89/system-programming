#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(void){
    
    int fd[2];
    char buff[100];
    pipe(fd);       //pipe creation

    pid_t pid = fork();

    if(pid < 0){
        perror("fork");
        return -1;
    }
    else if(pid == 0){
        //child process
        close(fd[0]);   //close the read end 
        
        char * msg = "Hello from parent";
        
        write(fd[1], msg, strlen(msg)+1);

        close(fd[1]);
    }
    else {
        //parent process
        close(fd[1]);   // close the write-end
        
        read(fd[0], buff, sizeof(buff));

        printf("Child : %s\n", buff);

        close(fd[0]);   
    }

    return 0 ;
}

