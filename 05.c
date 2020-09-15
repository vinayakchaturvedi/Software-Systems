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
[1] 51041
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$ ll /proc/51041/fd/
total 0
dr-x------ 2 vinayak vinayak  0 Sep 15 23:11 ./
dr-xr-xr-x 9 vinayak vinayak  0 Sep 15 23:11 ../
lrwx------ 1 vinayak vinayak 64 Sep 15 23:11 0 -> /dev/pts/2
lrwx------ 1 vinayak vinayak 64 Sep 15 23:11 1 -> /dev/pts/2
lrwx------ 1 vinayak vinayak 64 Sep 15 23:11 2 -> /dev/pts/2
lr-x------ 1 vinayak vinayak 64 Sep 15 23:11 3 -> /home/vinayak/Desktop/Study_Material/1stSem/SS/IJHandsOn/File5thQues0.txt
lr-x------ 1 vinayak vinayak 64 Sep 15 23:11 4 -> /home/vinayak/Desktop/Study_Material/1stSem/SS/IJHandsOn/File5thQues1.txt
lr-x------ 1 vinayak vinayak 64 Sep 15 23:11 5 -> /home/vinayak/Desktop/Study_Material/1stSem/SS/IJHandsOn/File5thQues2.txt
lr-x------ 1 vinayak vinayak 64 Sep 15 23:11 6 -> /home/vinayak/Desktop/Study_Material/1stSem/SS/IJHandsOn/File5thQues3.txt
lr-x------ 1 vinayak vinayak 64 Sep 15 23:11 7 -> /home/vinayak/Desktop/Study_Material/1stSem/SS/IJHandsOn/File5thQues4.txt
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$

*/