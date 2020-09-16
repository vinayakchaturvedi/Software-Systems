#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int fdMainFile = open("MainFileQues7.txt", O_RDONLY);
    const int max = 100000;
    if(fdMainFile == -1){
        char message[] = "File Doesn't Exist with name as \"MainFileQues7.txt\" hence creating one\n";
        write(2, message, sizeof(message)-1);
        //perror("Error");
        fdMainFile = open("MainFileQues7.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);
        char content[] = "This content is created from code file.";
        write(fdMainFile, content, sizeof(content) - 1);
        close(fdMainFile);
    }
    fdMainFile = open("MainFileQues7.txt", O_RDONLY);

    char content[max];
    read(fdMainFile, content, sizeof(content));
    int fdCopiedFile = open("CopiedFileQues7.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    int i = 0;
    while(content[i] != '\0'){
        char copiedContent[1] = { content[i++] };
        write(fdCopiedFile, copiedContent, sizeof(copiedContent));
    }

    close(fdMainFile);
    close(fdCopiedFile);
    return 0;
}