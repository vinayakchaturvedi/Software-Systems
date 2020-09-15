#include<stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
    char content[1500];

    read(1, content, sizeof(content));
    for(int i = 0; content[i] != '\0'; i++)
    {
        char temp[] = { content[i] };
        write(2, temp, sizeof(char));
    }

    return 0;
}