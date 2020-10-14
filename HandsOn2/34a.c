#include<stdio.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>

int main(){
    struct sockaddr_in server, client;
    int sockDesc, clientSockDesc, clientLen;
    char buff[1000];

    sockDesc = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(5555);

    bind(sockDesc, (struct sockaddr *)&server, sizeof(server));
    listen(sockDesc, 4);    //At max 4 clients can wait in the waiting queue at any time.

    char temp[] = "Waiting for the client...\n";
    int clientNum = 1;
    while(1){                       //Keep running and accept the incoming requests...
        printf("%s", temp);
        clientLen = sizeof(client);
        clientSockDesc = accept(sockDesc, (struct sockaddr *)&client, &clientLen);
        printf("Connected to a client number: %d\n", clientNum);

        if(!fork()){        //child to serve client's request
            close(sockDesc);        //close socket descriptor of parent because it is not required in serving the request by child.
            write(clientSockDesc, "Server has accepted the request.\n", sizeof("Server has accepted the request.\n"));
            read(clientSockDesc, buff, sizeof(buff));
            printf("Message from Client Number %d: %s\n\n", clientNum, buff);
            return 0;        //Terminate the child process
        }
        else{           //Parent -- continue accepting the request of other clients.
            clientNum++;
            close(clientSockDesc);   //Close client Socket Descriptor in parent because it is not required by parent.
        }
    }
    close(sockDesc);
    return 0;
}