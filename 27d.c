#include<stdio.h>
#include<unistd.h>

int main(){
    char *argument[3] = {"ls", "-Rl", NULL};

    execv("/bin/ls", argument);
    return 0;
}