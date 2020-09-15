#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdbool.h>
#include<string.h>

int main() {
    int i = 0;
    while(true){
        if(i<5){
            char temp[5];
            sprintf(temp, "%d", i);
            char fileName[] = "File5thQues";
            strcat(fileName, temp);
            strcat(fileName, ".txt");
            int fd = open(fileName, O_CREAT|O_RDONLY, 0644);
            i++;
        }

    }
}
