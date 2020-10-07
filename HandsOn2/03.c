#include<stdio.h>
#include<sys/time.h>
#include<string.h>
#include<sys/resource.h>

int main(){
    struct rlimit limit1;
    struct rlimit limit2;

    getrlimit(RLIMIT_NOFILE, &limit1);
    printf("Current value of number of file descriptor: %ld\n", limit1.rlim_cur);
    limit1.rlim_cur = 4;

    setrlimit(RLIMIT_NOFILE, &limit1);
    getrlimit(RLIMIT_NOFILE, &limit2);
    printf("After modification...\nUpdated value of number of file descriptor: %ld\n", limit1.rlim_cur);

    return 0;
}
