#include<stdio.h>
#include<unistd.h>

int main(){
    char *env_list[] = { "SOURCE=27c.c",
                         "TARGET=OUTPUT",
                         NULL};

    execle("/bin/ls", "ls", "-Rl", NULL, env_list);
    return 0;
}