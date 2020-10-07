#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

int main(){

    struct sigaction action;
    action.sa_handler = SIG_IGN;
    action.sa_flags = 0;
    sigaction(SIGINT, &action, NULL);
    printf("Ignoring the SIGINT signal...\n");
    sleep(5);

    action.sa_handler = SIG_DFL;
    sigaction(SIGINT, &action, NULL);
    printf("\n\nResetting to default action for SIGINT.\n");
    printf("Press \"Ctrl + C\" to test\n");
    sleep(5);
    printf("No SIGINT within 5 seconds.\n");

    return 0;
}
