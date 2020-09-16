#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    //-------------------------------Variable declaration--------------------------
    char p1[] = "Enter the name of the file that you want to copy: ", p2[] = "Enter the name of the target file: ";
    char temp[100], temp2[100], only1Char[1], only1Char2[1];
    int i = 0;

    //-------------------------------Get Name of file1--------------------------
    write(2, p1, sizeof(p1));
    read(1, only1Char, sizeof(char));
    while(only1Char[0] != '\n'){
        temp[i++] = only1Char[0];
        read(1, only1Char, sizeof(char));
    }

    char file1[i];
    for(int j = 0; j < i; j++){
        file1[j] = temp[j];
    }
    puts(file1);
    //-------------------------------Validate file1--------------------------
    int fdOfMainFile = open(file1, O_RDONLY);
    if(fdOfMainFile == -1){
        perror("Error");
        return -1;
    }

    //-------------------------------Get Name of file2--------------------------
    write(2, p2, sizeof(p2));
    int x = 0;
    read(1, only1Char2, sizeof(char));
    while(only1Char2[0] != '\n'){
        temp2[x++] = only1Char2[0];
        read(1, only1Char2, sizeof(char));
    }
    puts(temp2);
    //char file2[x];


    return 0;
}