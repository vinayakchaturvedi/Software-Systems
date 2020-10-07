#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include "18_record_struct.c"

int main(){

    int fd = open("18_db", O_RDONLY);

    struct Record test;
    fd = open("18_db", O_RDONLY);
    read(fd, &test, sizeof(test));
    printf("Record number: %d, Record Access count: %d\n", test.recordNumber, test.accessCount);
    read(fd, &test, sizeof(test));
    printf("Record number: %d, Record Access count: %d\n", test.recordNumber, test.accessCount);
    read(fd, &test, sizeof(test));
    printf("Record number: %d, Record Access count: %d\n", test.recordNumber, test.accessCount);

    close(fd);

    return 0;
}

