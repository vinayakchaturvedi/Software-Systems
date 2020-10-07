#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {

    char myFifo[] = "./myFifo";
    int res = mknod(myFifo, S_IFIFO|0644, 0);
    if(res == -1){
        perror("MyFifo with name as \"myFifo\" already exists");
    }
    return 0;
}
