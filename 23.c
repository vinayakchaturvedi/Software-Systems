#include<stdio.h>
#include<unistd.h>
#include <stdlib.h>

int main(){

    //create zombie -- child's processing is done and
    //waiting for exit status from parent and it can't be killed

    int childId = fork();
    if(childId){
        sleep(10);
        printf("This is Parent with id: %d and going to terminate now\n", getpid());
    }
    else{
        printf("This is child with id: %d and my processing is done\n", getpid());
        exit(0);
    }

    return 0;
}
/*
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$ cc 23.c
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$ ./a.out &
[1] 5093
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$ This is child with id: 5094 and my processing done
^C
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$ head /proc/5094/status
Name:	a.out
State:	Z (zombie)
Tgid:	5094
Ngid:	0
Pid:	5094
PPid:	5093
TracerPid:	0
Uid:	1000	1000	1000	1000
Gid:	1000	1000	1000	1000
FDSize:	0
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$ fg
./a.out
This is Parent with id: 5093 and going to terminate now
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$
*/