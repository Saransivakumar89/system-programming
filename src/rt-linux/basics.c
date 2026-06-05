#define _GNU_SOURCE

#include<stdio.h>
#include<sched.h>
#include<unistd.h>


int main(void){
    
#ifdef NOT
    struct sched_param param;

    param.sched_priority = 50; /* Mid-range RT priority*/

    sched_setscheduler(0, SCHED_FIFO, &param);
#endif
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

