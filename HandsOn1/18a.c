#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include "18_record_struct.c"

int main(){

    //------------------------------------------------------Variable Declaration------------------------------------------------------
    int fd = open("18_db", O_RDWR);
    struct Record record;
    int recordNum;
    printf("Enter the record number (1, 2, 3) that you want to write lock: ");
    scanf("%d", &recordNum);
    getchar();

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = ((recordNum-1) * sizeof(record));
    lock.l_len = sizeof(record);
    lock.l_pid = getpid();

    //------------------------------------------------------Check lock------------------------------------------------------
    printf("Before entering critical section.\n");
    fcntl(fd, F_SETLKW, &lock);

    //------------------------------------------------------Inside Critical section--------------------------------------------------
    printf("Inside Critical section...\n");

    lseek(fd, ((recordNum-1) * sizeof(record)), SEEK_SET);
    read(fd, &record, sizeof(record));
    printf("For Record Number: %d, old Record Access count is: %d\n", record.recordNumber, record.accessCount);

    record.accessCount = record.accessCount + 1;

    printf("Record accessCount has been updated and new accessCount is: %d\n", record.accessCount);
    lseek(fd, ((recordNum-1) * sizeof(record)), SEEK_SET);
    write(fd, &record, sizeof(record));

    printf("Press enter to unlock...\n");
    getchar();

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("Record is Unlocked Now...\n");

    //------------------------------------------------------Unlocked Now--------------------------------------------------
    close(fd);

    return 0;
}

