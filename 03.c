#include<stdio.h>
#include <fcntl.h>

int main() {

    char fileName[] = "FileFrom3rd.txt";
    int fd = creat(fileName, 0644);
    printf("%d\n", fd);

    return 0;
}
