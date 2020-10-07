#include<stdio.h>
#include<unistd.h>

int main(){
    char *argument[3] = {"ls", "-Rl", NULL};

    execvp("ls", argument);
    return 0;
}