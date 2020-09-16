#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){

    //----------------------------------------Opening the file--------------------------------------
    int fdMainFile = open("MainFileQues8.txt", O_RDONLY);
    const int max = 10000;
    if(fdMainFile == -1){
    //----------------------------------------File doesn't exists hence creating one----------------------
        char message[] = "File Doesn't Exists with name as \"MainFileQues8.txt\" hence creating one\n";
        write(2, message, sizeof(message)-1);
        //perror("Error");
        fdMainFile = open("MainFileQues8.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);
        char content[] = "1. This is 1st line.\n2. This is 2nd line.\0";
        write(fdMainFile, content, sizeof(content) - 1);
        close(fdMainFile);
    }

    //----------------------------------------Opening the main file in readOnly mode--------------------------------------
    fdMainFile = open("MainFileQues8.txt", O_RDONLY);

    //----------------------------------------Reading the content of main file and Displaying-----------------------------
    char content[1];
    read(fdMainFile, content, sizeof(content));
    while(content[0] != '\0'){
        int i = 0;
        char line[max];
        while(content[0] != '\n' && content[0] != '\0'){
            line[i++] = content[0];
            read(fdMainFile, content, sizeof(content));
        }
        line[i++] = '\n';
        write(2, line, sizeof(char)*i);
        if(content[0] == '\0') {
            break;
        }
        read(fdMainFile, content, sizeof(content));
    }

    //----------------------------------------Closing both FD--------------------------------------
    close(fdMainFile);

    return 0;
}