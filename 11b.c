#include<stdio.h>
#include<unistd.h>
#include <fcntl.h>
#include<string.h>

int main(){

    int originalFileDescriptor = open("MainFileQues11b.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    char content1[] = "Dummy Content...";
    write(originalFileDescriptor, content1, sizeof(content1) - 1);

    int duplicateFileDescriptor = dup2(originalFileDescriptor, 10);

    char newContent[60];
    char temp[2];

    sprintf(temp, "%d", originalFileDescriptor);
    strcat(newContent, "\nOriginal FileDescriptor:  ");
    strcat(newContent, temp);

    sprintf(temp, "%d", duplicateFileDescriptor);
    strcat(newContent, "\nDuplicate FileDescriptor: ");
    strcat(newContent, temp);
    strcat(newContent, "\n");

    write(originalFileDescriptor, newContent, sizeof(newContent) - 1);

    close(originalFileDescriptor);
    close(duplicateFileDescriptor);

    return 0;
}
/*
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$ cc 11b.c
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$ ./a.out
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$ cat MainFileQues11b.txt
Dummy Content...�
Original FileDescriptor:  3
Duplicate FileDescriptor: 10
vinayak@vinayak-Lenovo-G50-70:~/Desktop/Study_Material/1stSem/SS/IJHandsOn$
*/