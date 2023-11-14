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

    bzero(sndmsg, 50); 
    bzero(rcvmsg, 50); 
    bzero(&serv, sizeof(serv)); 

    serv.sin_family = AF_INET; 
    serv.sin_port = htons(6969); 
    serv.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    sock_fd = socket(AF_INET, SOCK_STREAM, 0); 

    connect(sock_fd, (struct sockaddr*)&serv, sizeof(serv)); 

    printf("Enter string: "); 
    fgets(sndmsg, 50, stdin);
    send(sock_fd, sndmsg, sizeof(sndmsg), 0); 
    printf("\nThe length of the string is: ");  
    int n = 0;
    recv(sock_fd,&n, sizeof(n), 0);
    printf("%d", n); 

    close(sock_fd); 
    return 0;
}