#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include "18_record_struct.c"

int main(){

    int fd = open("18_db", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    struct Record record1, record2, record3;
    record1.recordNumber = 1;
    record1.accessCount = 0;
    write(fd, &record1, sizeof(record1));

    record2.recordNumber = 2;
    record2.accessCount = 0;
    write(fd, &record2, sizeof(record2));

    record3.recordNumber = 3;
    record3.accessCount = 0;
    write(fd, &record3, sizeof(record3));

    close(fd);

    printf("Checking the initialization of DB...\n");
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

