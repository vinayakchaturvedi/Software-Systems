#include<stdio.h>
#include <fcntl.h>
#include<unistd.h>

int main() {

    int fdWithOutExcl = open("File1WithoutEXCL4thQ.txt", O_RDWR);
    if(fdWithOutExcl == -1){
        perror("Error");
    }
    else{
        printf("File Exists\n");
    }
    close(fdWithOutExcl);

    //Use O_EXCEL FLAG
    int fdWithExcl = open("File1WithEXCL4thQ.txt", O_CREAT|O_RDWR|O_EXCL, 0644);
    if(fdWithExcl == -1){
        perror("Error");
    }
    else{
        printf("File doesn't exists\n");
    }
    close(fdWithExcl);
    return 0;
}
