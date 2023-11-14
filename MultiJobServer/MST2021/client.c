#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int sock_fd;
    char sndmsg[50], rcvmsg[50]; 
    struct sockaddr_in serv; 

    struct descriptor{
        short fd1, fd2; 
    } D;

    D.fd1 = socket(AF_INET, SOCK_STREAM, 0); 
    D.fd2 = socket(AF_INET, SOCK_STREAM, 0); 

    bzero(sndmsg, 50); 
    bzero(rcvmsg, 50); 
    bzero(&serv, sizeof(serv)); 

    serv.sin_family = AF_INET; 
    serv.sin_port = htons(6969); 
    serv.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    sock_fd = socket(AF_INET, SOCK_STREAM, 0); 

    connect(sock_fd, (struct sockaddr*)&serv, sizeof(serv)); 

    printf("Sending the descriptors\n");
    send(sock_fd, &D, sizeof(D), 0);
    int n = 0;
    
    struct result {
        short max;
    } M; 

    recv(sock_fd, &M, sizeof(M),0); 

    if(M.max==D.fd1)
        printf("fd1 is larger\n"); 
    else if(M.max==D.fd2) 
        printf("fd2 is larger\n");
    else{
        printf("error!\n");
        exit(1);
    }

    close(sock_fd); 
    return 0;
}