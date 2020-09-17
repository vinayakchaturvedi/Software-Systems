#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<fcntl.h>

int main(){

    int file = open("MainFileQues10.txt", O_CREAT|O_RDWR|O_TRUNC, 0644);
    char content[] = "Dummy1 ...";
    write(file, content, 10);

    int lseekOutput = lseek(file, 20, SEEK_SET);

    char content2[] = "Dummy2 ...";
    write(file, content2, 10);

    printf("Return value of lseek is: %d\n", lseekOutput);
    close(file);

    return 0;
}