#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main() {

    int targetFile = open("SoftLink_Target.txt", O_CREAT|O_WRONLY|O_TRUNC, 0644);
    char content[] = "This content is from SoftLink original file";
    write(targetFile, content, sizeof(content) - 1);
    close(targetFile);

    const char target[] = "./SoftLink_Target.txt";
    const char linkPath[] = "./SoftLink_Result.txt";

    int softLink = symlink(target, linkPath);
    if(softLink == -1){
        perror("SoftLink already exists with name as \"SoftLink_Result.txt\"");
    }
	return 0;
}
