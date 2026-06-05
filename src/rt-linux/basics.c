#define _GNU_SOURCE

#include<stdio.h>
#include<sched.h>
#include<unistd.h>


int main(void){
    

    int policy = sched_getscheduler(0);

    switch(policy){
    
        case SCHED_FIFO:
            printf("FIFO\n");
            break;
        
        case SCHED_RR:
            printf("RR\n");
            break;

        case SCHED_OTHER:
            printf("OTHER\n");
            break;

        case SCHED_BATCH:
            printf("BATCH\n");
            break;

        case SCHED_IDLE:
            printf("IDLE\n");
            break;

        default:
            printf("policy : %d\n", policy);
            break;
    }


    return 0 ;
}

