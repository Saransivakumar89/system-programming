#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/wait.h>

char *create_mb(int mb){
    size_t bytes = 1024 * 1024 * mb;
    char *data = malloc(bytes);
    if (!data) {
        perror("malloc");
        exit(1);
    }
    return data;
}

int main(void){
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        return -1;
    }

    int mb_size = 10;
    size_t bytes = mb_size * 1024 * 1024;

    char *mb = create_mb(mb_size);
    memset(mb, '*', bytes);

    pid_t pid = fork();

    if(pid < 0){
        perror("fork");
        return -1;
    }
    else if(pid == 0){
        // Child: Reader
        close(fd[1]);

        char buf[4096];
        ssize_t n;
        ssize_t total = 0;

        while ((n = read(fd[0], buf, sizeof(buf))) > 0) {
            total += n;
        }

        if (n < 0) {
            perror("read");
        }

        printf("Child: Read %zd bytes\n", total);

        close(fd[0]);
        exit(EXIT_SUCCESS);
    }
    else{
        // Parent: Writer
        close(fd[0]);

        size_t total = 0;

        while(total < bytes){
            ssize_t n = write(fd[1], mb + total, bytes - total);
            if (n <= 0) {
                perror("write");
                break;
            }
            total += n;
        }

        printf("Parent: Wrote %zu bytes\n", total);

        close(fd[1]);
        wait(NULL);
    }

    free(mb);
    return 0;
}
