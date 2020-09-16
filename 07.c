#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){

    //----------------------------------------Opening the main file--------------------------------------
    int fdMainFile = open("MainFileQues7.txt", O_RDONLY);
    const int max = 100000;
    if(fdMainFile == -1){
    //----------------------------------------Main file doesn't exists hence creating one----------------------
        char message[] = "File Doesn't Exists with name as \"MainFileQues7.txt\" hence creating one\n";
        write(2, message, sizeof(message)-1);
        //perror("Error");
        fdMainFile = open("MainFileQues7.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);
        char content[] = "This content is created from code file.";
        write(fdMainFile, content, sizeof(content) - 1);
        close(fdMainFile);
    }

    //----------------------------------------Opening the main file in readOnly mode--------------------------------------
    fdMainFile = open("MainFileQues7.txt", O_RDONLY);

    //----------------------------------------Reading the content of main file------------------------------------
    char content[max];
    read(fdMainFile, content, sizeof(content));

    //----------------------------------------Creating copied file and writing to it--------------------------------------
    int fdCopiedFile = open("CopiedFileQues7.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    int i = 0;
    while(content[i] != '\0'){
        char copiedContent[1] = { content[i++] };
        write(fdCopiedFile, copiedContent, sizeof(copiedContent));
    }

    //----------------------------------------Closing both FD--------------------------------------
    close(fdMainFile);
    close(fdCopiedFile);
    return 0;
}