#include<stdio.h>
#include<unistd.h>

int main(){
    execl("./Greet", "Greet", NULL);
    return 0;
}