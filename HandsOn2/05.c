#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<unistd.h>

int main(){

    printf("Maximum length of the argument to the exec family of functions: %ld\n", sysconf(_SC_ARG_MAX));
    printf("Maximum number of simultaneous process per user id:             %ld\n", sysconf(_SC_CHILD_MAX));
    printf("Number of clock ticks per second:                               %ld\n", sysconf(_SC_CLK_TCK));

    printf("Maximum number of open files:                                   %ld\n", sysconf(_SC_OPEN_MAX));
    printf("Size of a page:                                                 %ld\n", sysconf(_SC_PAGESIZE));
    printf("Total number of pages in the physical memory:                   %ld\n", sysconf(_SC_PHYS_PAGES));

    printf("Number of currently available pages in the physical memory:     %ld\n", sysconf(_SC_AVPHYS_PAGES));

    return 0;
}
