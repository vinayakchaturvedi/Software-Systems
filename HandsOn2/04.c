#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/time.h>
#include<sys/stat.h>
#include<sys/types.h>

unsigned long long rdtsc(void){
    unsigned long long dst;
    __asm__ __volatile__ ("rdtsc" : "=A"(dst));
    return dst;
}

int main(){
    long long int start, end;
    start = rdtsc();
    for(int i = 0; i < 100; i++){
        getppid();
    }
    end = rdtsc();
    printf("Total Cycles taken = %llu\n", end - start);
    printf("Time taken: %f nano seconds\n", (end - start) / 1.2);       //Divide by CPU freq --> cpu MHz : 1280.834

    return 0;
}
