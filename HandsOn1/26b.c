#include<stdio.h>
#include<unistd.h>

int main(){
    execl("./Greet", "Greet", "Hello, This is from command line argument...", NULL);
    return 0;
}