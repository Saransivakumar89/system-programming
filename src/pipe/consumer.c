#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<string.h>

#define FIFO "/tmp/fifo"

int main(void){
    
    int arr[10], count = 0;
    
    int fd = open(FIFO,O_RDONLY);
    
    int val, sum = 0;
    if(fd < 0){
        perror("open");
        return -1;
    }
    

    while(read(fd,&val,sizeof(val))>0){
        sum += val;
        count++;
    }
    
    int avg = sum/count;

    printf("sum: %d\nAvg: %d\n", sum,avg);
    
    close(fd);
    return 0 ;
}

