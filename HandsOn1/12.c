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
    int mode = fcntl(fileDescriptor, F_GETFL) & O_ACCMODE;
    printf("Current Mode is: %s\n", mode == O_RDONLY ? "ReadOnly" : "Wrong");
    close(fileDescriptor);

    //----------------------Check WriteOnly------------------------------------------
    fileDescriptor = open("MainFileQues12.txt", O_WRONLY);
    mode = fcntl(fileDescriptor, F_GETFL) & O_ACCMODE;
    printf("Current Mode is: %s\n", mode == O_WRONLY ? "WriteOnly" : "Wrong");
    close(fileDescriptor);

    //----------------------Check ReadWrite------------------------------------------
    fileDescriptor = open("MainFileQues12.txt", O_RDWR);
    mode = fcntl(fileDescriptor, F_GETFL) & O_ACCMODE;
    printf("Current Mode is: %s\n", mode == O_RDWR ? "ReadWrite" : "Wrong");
    close(fileDescriptor);

    return 0;
}