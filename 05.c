#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdbool.h>
#include<string.h>

int main() {
    int i = 0;
    while(true){
        if(i<5){
            char temp[5];
            sprintf(temp, "%d", i);
            char fileName[] = "File5thQues";
            strcat(fileName, temp);
            strcat(fileName, ".txt");
            int fd = open(fileName, O_CREAT|O_RDONLY, 0644);
            i++;
        }
    }
}
/*
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$ cc 05.c
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$ ./a.out &
[1] 8670
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$ ll /proc/8670/fd/
total 0
dr-x------ 2 vinayak vinayak  0 Sep 16 20:47 ./
dr-xr-xr-x 9 vinayak vinayak  0 Sep 16 20:47 ../
lrwx------ 1 vinayak vinayak 64 Sep 16 20:47 0 -> /dev/pts/1
lrwx------ 1 vinayak vinayak 64 Sep 16 20:47 1 -> /dev/pts/1
lrwx------ 1 vinayak vinayak 64 Sep 16 20:47 2 -> /dev/pts/1
lr-x------ 1 vinayak vinayak 64 Sep 16 20:47 3 -> /home/vinayak/Desktop/Study_Material/1stSem/SS/IJHandsOn/File5thQues0.txt
lr-x------ 1 vinayak vinayak 64 Sep 16 20:47 4 -> /home/vinayak/Desktop/Study_Material/1stSem/SS/IJHandsOn/File5thQues1.txt
lr-x------ 1 vinayak vinayak 64 Sep 16 20:47 5 -> /home/vinayak/Desktop/Study_Material/1stSem/SS/IJHandsOn/File5thQues2.txt
lr-x------ 1 vinayak vinayak 64 Sep 16 20:47 6 -> /home/vinayak/Desktop/Study_Material/1stSem/SS/IJHandsOn/File5thQues3.txt
lr-x------ 1 vinayak vinayak 64 Sep 16 20:47 7 -> /home/vinayak/Desktop/Study_Material/1stSem/SS/IJHandsOn/File5thQues4.txt
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$ kill -9 8670
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$ ps
    PID TTY          TIME CMD
   8522 pts/1    00:00:00 bash
   8677 pts/1    00:00:00 ps
[1]+  Killed                  ./a.out
*/