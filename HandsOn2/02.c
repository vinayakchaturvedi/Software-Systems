#include<stdio.h>
#include<sys/time.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<sys/resource.h>

int main(){
    struct rlimit limits;
    char s1[5][20] = {
        "RLIMIT_CPU", "RLIMIT_CORE", "RLIMIT_FSIZE",
        "RLIMIT_NOFILE", "RLIMIT_NPROC"
    };

    int s[5] = {
        RLIMIT_CPU, RLIMIT_CORE, RLIMIT_FSIZE,
        RLIMIT_NOFILE, RLIMIT_NPROC
    };

    for(int i = 0; i < 5; i++){
        getrlimit(s[i], &limits);
        printf("%s: Soft limit: %lu\t Hard limit: %lu\n", s1[i], limits.rlim_cur,
                limits.rlim_max);
    }
    return 0;
}
