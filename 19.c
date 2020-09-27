#include<stdio.h>
#include<unistd.h>
#include<time.h>

int main(){

    clock_t time;
    time = clock();
    getpid();

    time = clock() - time;
    double totalTime = ((double)time)/CLOCKS_PER_SEC;
    printf("Total time taken by \"getpid()\" to execute is: %f\n", totalTime);

    return 0;
}