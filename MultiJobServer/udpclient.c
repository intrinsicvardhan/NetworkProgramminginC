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
    char rcvmsg[50], sndmsg[50]; 
    struct sockaddr_in serv; 
    socklen_t len;

    bzero(rcvmsg, 50); 
    bzero(sndmsg, 50); 
    bzero(&serv, sizeof(serv)); 

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0); 

    serv.sin_family = AF_INET; 
    serv.sin_port = htons(6969); 
    serv.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    while(1) {
        len = sizeof(serv);
        fgets(sndmsg, sizeof(sndmsg), stdin); 
        sendto(sock_fd, sndmsg, strlen(sndmsg), 0, (struct sockaddr*)&serv, sizeof(serv)); 

        
        recvfrom(sock_fd, rcvmsg, sizeof(rcvmsg), 0, (struct sockaddr*)&serv, &len); 
        printf("Message received: %s", rcvmsg);
        close(sock_fd); 
        exit(0);           
    }
    return 0;
}