#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(void){
    
    int fd[2];
    char buff[100];
    int arr[5] = {1,4,23,67, 89};
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
        
       // write(fd[1], msg, strlen(msg)+1);

        write(fd[1], arr, sizeof(arr));

        close(fd[1]);
    }
    else {
        //parent process
        close(fd[1]);   // close the write-end
        
        read(fd[0], buff, sizeof(buff));

        for(int i = 0 ; i < 5 ; i++){
            printf("%d ", arr[i]);
        }
        printf("\n");

        //printf("Child : %s\n", buff);

        close(fd[0]);   
    }

    return 0 ;
}

