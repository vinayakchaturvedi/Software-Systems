#include<stdio.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<pthread.h>
#include<unistd.h>

#define ADMIN 1
#define NORMAL_USER 2
#define JOINT_ACCOUNT 3

void *connectionHandler(void *sd){
    int clientSockDesc = *(int*)sd;
    char buff[1000];

    printf("Connected to a client...\n");
    char temp[] = "Server has accepted the request.\nEnter \"1\" for Administrator login \"2\" for Normal User login \"3\" for Joint Account holder login: ";
    write(clientSockDesc, temp, sizeof(temp) - 1);

    //--------------------------Get the user type whether user is admin, normal user, joint account holder----------------

    read(clientSockDesc, buff, sizeof(buff));
    printf("Message from Client: %s\n\n", buff);
    return 0;
}

int main(){
    struct sockaddr_in server, client;
    int sockDesc, clientSockDesc, clientLen;
    char buff[1000];
    pthread_t threads;

    sockDesc = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5555);

    bind(sockDesc, (struct sockaddr *)&server, sizeof(server));
    listen(sockDesc, 4);    //At max 4 clients can wait in the waiting queue at any time.

    char temp[] = "Waiting for the client...\n";

    while(1){                       //Keep running and accept the incoming requests...
        printf("%s", temp);
        clientLen = sizeof(client);
        clientSockDesc = accept(sockDesc, (struct sockaddr *)&client, &clientLen);
        if(pthread_create(&threads, NULL, connectionHandler, (void *) &clientSockDesc) < 0){
            perror("Not able to create the thread");
            return -1;
        }
    }
    pthread_exit(NULL);
    close(sockDesc);
    return 0;
}