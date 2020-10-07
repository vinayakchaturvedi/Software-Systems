#include<stdio.h>
#include<unistd.h>

int main(){
    execl("/bin/ls", "ls", "-Rl", NULL);
    return 0;
}