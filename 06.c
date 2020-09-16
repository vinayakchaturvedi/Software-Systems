#include<stdio.h>
#include <unistd.h>

int main(){
    char content[1500];

    int numOfBytes = read(1, content, sizeof(content));
    write(2, content, numOfBytes);

    return 0;
}