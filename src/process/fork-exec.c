#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

#define N 3   

/*
 * creates multiple child processes using fork().
 * Each child process executes a different command using execvp().
 * The parent process waits for all children to finish process.
 */

int main(void){

    pid_t pid[N];  // Array to store child PIDs
    char *cmds[] = {"whoami", "date", "ls"};

    // Create N child processes
    for(int i = 0 ; i < N ; i++){
        pid[i] = fork();   

        if(pid[i] < 0){
            // Error in fork
            perror("fork");
            return -1;
        }
        else if(pid[i] == 0){
            // Child process block
            
            if(i == 0){
                sleep(1);
              char *args[] = {"whoami", NULL};
                execvp(cmds[i], args);
            }
            else if(i == 1){
                sleep(2);
               char *args[] = {"date", NULL};
                execvp(cmds[i], args);
            }
            else{
                sleep(3);
                char *args[] = {"ls", NULL};
                execvp(cmds[i], args);
            }

            // If execvp() fails, this line will execute
            perror("exec failed");
            exit(1);
        }
        
    }

    // Parent waits for all child processes
    for(int i = 0; i < N ; i++){
        waitpid(pid[i], NULL, 0);  
    }
    sleep(1);
    printf("All child processes completed.\n");

    return 0;
}
