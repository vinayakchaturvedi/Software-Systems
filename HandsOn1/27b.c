#include<stdio.h>
#include<unistd.h>

int main(){
    execlp("ls", "ls", "-Rl", NULL);
    return 0;
}