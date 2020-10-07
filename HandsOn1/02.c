#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include <unistd.h>
#include <fcntl.h>


int main() {

    int pid = getpid();
    char process[25];
    sprintf(process, "%d" , pid);
    strcat(process, "/status");
    char fileName[] = "/proc/";

    strcat(fileName, process);
    int fd = open(fileName, O_RDONLY);

    char content[1550];
    read(fd, content, sizeof(content));
    printf("Printing status for the current process with Process id: %d\n", pid);
    puts(content);
    close(fd);
    while(true);

    return 0;
}
