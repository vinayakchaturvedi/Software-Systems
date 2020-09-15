#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main() {

    int originalFile = open("HardLink_Old.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    char content[] = "This content is from the HardLink original file";
    write(originalFile, content, sizeof(content) - 1);
    close(originalFile);

    char oldPath[] = "./HardLink_Old.txt";
    char newPath[] = "./HardLink_New.txt";

    int hardLink = link(oldPath, newPath);
    if(hardLink == -1){
        perror("HardLink already exists with name as \"HardLink_New.txt\"");
    }
	return 0;
}
