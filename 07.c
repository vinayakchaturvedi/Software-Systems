#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    //-------------------------------Variable declaration--------------------------
    char p1[] = "Enter the name of the file that you want to copy: ", p2[] = "Enter the name of the target file: ";
    char temp[100], temp2[100], only1Char[1];
    int i = 0;
    const int max = 100000;

    //-------------------------------Get Name of file1--------------------------
    write(2, p1, sizeof(p1));
    read(1, only1Char, sizeof(char));
    while(only1Char[0] != '\n'){
        temp[i++] = only1Char[0];
        read(1, only1Char, sizeof(char));
    }

    char file1[i+1];
    for(int j = 0; j < i; j++){
        file1[j] = temp[j];
    }
    file1[i] = '\0';
    //-------------------------------Validate file1--------------------------
    int fdOfMainFile = open(file1, O_RDONLY);
    if(fdOfMainFile == -1){
        perror("Error");
        return -1;
    }

    //-------------------------------Get Name of file2--------------------------
    i = 0;
    write(2, p2, sizeof(p2));
    read(1, only1Char, sizeof(char));
    while(only1Char[0] != '\n'){
        temp2[i++] = only1Char[0];
        read(1, only1Char, sizeof(char));
    }
    char file2[i+1];
    for(int j = 0; j < i; j++){
        file2[j] = temp2[j];
    }
    file2[i] = '\0';

    //----------------------------------------Reading the content of main file------------------------------------
    char content[max];
    read(fdOfMainFile, content, sizeof(content));

    //----------------------------------------Creating copied file and writing to it--------------------------------------
    int fdCopiedFile = open(file2, O_CREAT|O_WRONLY|O_TRUNC, 0644);
    i = 0;
    while(content[i] != '\0'){
        char copiedContent[1] = { content[i++] };
        write(fdCopiedFile, copiedContent, sizeof(copiedContent));
    }

    //----------------------------------------Closing both FD--------------------------------------
    close(fdOfMainFile);
    close(fdCopiedFile);

    return 0;
}