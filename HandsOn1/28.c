#include<stdio.h>
#include<sched.h>

int main(){

    int minPriorityOfRR = sched_get_priority_min(SCHED_RR);
    int maxPriorityOfRR = sched_get_priority_max(SCHED_RR);

    printf("Minimum Priority of RR: %d Maximum Priority of RR: %d \n", minPriorityOfRR, maxPriorityOfRR);

    int minPriorityOfFIFO = sched_get_priority_min(SCHED_FIFO);
    int maxPriorityOfFIFO = sched_get_priority_max(SCHED_FIFO);

    printf("Minimum Priority of FIFO: %d Maximum Priority of FIFO: %d \n", minPriorityOfFIFO, maxPriorityOfFIFO);

    return 0;
}