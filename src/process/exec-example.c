#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/wait.h>

/*
 * exec*() replaces current process image.
 * Only first successful exec() runs.
 */

/*
 * execl  -> /bin/ls -l
 * execv  -> /bin/pwd
 * execlp -> whoami
 * execvp -> date
 * execle -> /bin/env   (MY_VAR=Helloworld)
 * execve -> /bin/env   (MY_NAME=Saran)
 */

/*
 * - No return on success
 * - PATH search: only execlp, execvp
 * - argv/envp must be NULL terminated
 */

int main(void){
 
 #ifdef EXEC   
   char * arg1[] = {"pwd", NULL}; 
   char * arg2[] = {"whoami", NULL};
   char * arg3[] = {"date", NULL}; 
   char *env[] = {"MY_VAR=Helloworld",NULL};

    if(execl("/bin/ls","ls","-l",NULL)==-1){
        perror("exec failed");
        return -1;
    }

    if(execv("/bin/pwd", arg1)==-1){
        perror("exec failed");
        return -1;
    }   
   
    if(execlp("whoami", "whoami", NULL)==-1){
        perror("exec failed");
        return -1;
    }

    if(execvp("date", arg3)==-1){
        perror("exec failed");
        return -1;
    }

    if(execle("/bin/env", "env",NULL,env)==-1){
        perror("exec failed");
        return -1;
    }
 
    char * arg4[] = {"env", NULL};
    char * env1[] = {"MY_NAME=Saran", NULL};

    if(execve("/bin/env", arg4, env1)==-1){
        perror("exec failed");
        return -1;
    }
#endif

    return 0 ;
}

