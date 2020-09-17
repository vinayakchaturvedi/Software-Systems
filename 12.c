#include<stdio.h>
#include <fcntl.h>
#include<unistd.h>

int main(){

    //---------------Creating the file----------------------------------------------
    int fileDescriptor = open("MainFileQues12.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    char content1[] = "Dummy Content...";
    write(fileDescriptor, content1, sizeof(content1) - 1);
    close(fileDescriptor);

    //----------------------Check ReadOnly------------------------------------------
    fileDescriptor = open("MainFileQues12.txt", O_RDONLY);
    printf("Check ReadOnly:  %d\n", fcntl(fileDescriptor, F_GETFL));
    close(fileDescriptor);

    //----------------------Check WriteOnly------------------------------------------
    fileDescriptor = open("MainFileQues12.txt", O_WRONLY);
    printf("Check WriteOnly: %d\n", fcntl(fileDescriptor, F_GETFL));
    close(fileDescriptor);

    //----------------------Check ReadWrite------------------------------------------
    fileDescriptor = open("MainFileQues12.txt", O_RDWR);
    printf("Check ReadWrite: %d\n", fcntl(fileDescriptor, F_GETFL));
    close(fileDescriptor);

    return 0;
}