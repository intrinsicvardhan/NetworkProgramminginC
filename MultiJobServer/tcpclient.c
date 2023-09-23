#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    int sock_fd; 
    char sndmsg[50], rcvmsg[50]; 
    struct sockaddr_in serv;

    bzero(sndmsg, 50); 
    bzero(rcvmsg, 50); 
    bzero(&serv, sizeof(serv)); 

    serv.sin_family = AF_INET; 
    serv.sin_port = htons(6969); 
    serv.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    sock_fd = socket(AF_INET, SOCK_STREAM, 0); 

    connect(sock_fd, (struct sockaddr*)&serv, sizeof(serv)); 

    while(1) {
        printf("Enter message: "); 
        fgets(sndmsg, 100, stdin); 
         send(sock_fd, sndmsg, strlen(sndmsg), 0); 
         recv(sock_fd, rcvmsg, sizeof(rcvmsg), 0); 
         printf("Message received: %s", rcvmsg); 

        close(sock_fd); 
        exit(0);

    }
}