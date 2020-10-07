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
    printf("Initial value = %llu\n", start);
    for(int i = 0; i < 100; i++){
        getppid();
    }
    end = rdtsc();
    printf("End Value = %llu\n", end);
    end = end - start;
    printf("Cycle taken = %llu\n", end);

    return 0;
}
