#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    //-------------------------------Variable declaration--------------------------
    char p1[] = "Enter the name of the file that you want to copy: ", p2[] = "Enter the name of the target file: ";
    char temp[100];
    const int max = 100000;

    //-------------------------------Get Name of file1--------------------------
    write(2, p1, sizeof(p1));
    int bytesRead = read(1, temp, sizeof(temp));
    char file1[bytesRead];
    for(int j = 0; j < bytesRead - 1; j++){
        file1[j] = temp[j];
    }
    file1[bytesRead-1] = '\0';

    //-------------------------------Validate file1--------------------------
    int fdOfMainFile = open(file1, O_RDONLY);
    if(fdOfMainFile == -1){
        perror("Error");
        return -1;
    }

    //-------------------------------Get Name of file2--------------------------
    write(2, p2, sizeof(p2));
    bytesRead = read(1, temp, sizeof(temp));
    char file2[bytesRead];
    for(int j = 0; j < bytesRead - 1; j++){
        file2[j] = temp[j];
    }
    file2[bytesRead - 1] = '\0';

    //----------------------------------------Reading the content of main file------------------------------------
    char content[max];
    bytesRead = read(fdOfMainFile, content, sizeof(content));

    //----------------------------------------Creating copied file and writing to it--------------------------------------
    int fdCopiedFile = open(file2, O_CREAT|O_WRONLY|O_TRUNC, 0644);
    write(fdCopiedFile, content, bytesRead);

    //----------------------------------------Closing both FD--------------------------------------
    close(fdOfMainFile);
    close(fdCopiedFile);

    return 0;
}