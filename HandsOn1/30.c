#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <time.h>

int main(){

    int hour, min, sec;
    printf("Enter the time at which you want to script to be executed\nHour: ");
    scanf("%d", &hour);
    printf("Minute: ");
    scanf("%d", &min);

    if(!fork()){            //child
        printf("Child process id: %d\n", getpid());
        setsid();
        chdir("/");
        umask(0);

        time_t rawtime;
        struct tm* timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        while(1){
            if(timeinfo->tm_hour == hour && timeinfo->tm_min == min){
                execlp("ls", "ls", "-lrt", "/home/", NULL);
                printf("Done");
                break;
            }
            time(&rawtime);
            timeinfo = localtime(&rawtime);
        }
    }
    else{
        exit(0);
    }

    return 0;
}