#include<stdio.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>

int main(){
    struct sockaddr_in server;
    int sockDesc, messageLen;
    char buff[50];
    char result;

    sockDesc = socket(AF_INET, SOCK_STREAM, 0);     //Establishing the connection b/w client and server.
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1"); //Loop back address because both are on same machine.
                                // can give INADDR_ANY as well for same machine and if server is on diff machine
                                //provide its IP address in this field.
    server.sin_port = htons(5555);
    printf("Waiting to connect to the server...\n");
    int connectionStatus = connect(sockDesc, (struct sockaddr *)&server, sizeof(server));      //Sending the connect request to server.

    int retryCount = 0;
    while(connectionStatus == -1 && retryCount < 3){
        printf("Connection failed with server... Retrying in 3 seconds.\n");
        retryCount++;
        sleep(3);
        connectionStatus = connect(sockDesc, (struct sockaddr *)&server, sizeof(server));      //Again Sending the connect request to server.
    }
    if(connectionStatus == -1){
        printf("Could not establish the connection with server even after %d retries hence terminating the request now.\n", retryCount);
        return -1;
    }

    read(sockDesc, buff, sizeof(buff));
    printf("%s\n", buff);
    printf("Enter the message that you want to send to server: ");
    scanf(" %[^\n]", buff);
    write(sockDesc, buff, sizeof(buff));

    close(sockDesc);
    return 0;
}