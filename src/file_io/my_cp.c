#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(int argc, char *argv[]){
    
    if(argc!=3){
         printf("error: src-dest missing\n");
         exit(0);
    }

    int src = open(argv[1], O_RDONLY);

    if(src < 0){
        perror("open");
        return -1;
    }

    int dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC , 0666);

    if(dest < 0){
        perror("open");
        close(src);
        return -1;
    }

    char buff[100];

    ssize_t bytes;

    while((bytes = read(src,buff,sizeof(buff))) > 0)
    {
        write(dest,buff,bytes);
    }

    close(src);
    close(dest);

    return 0 ;
}

