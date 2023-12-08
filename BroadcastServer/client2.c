#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main() {
    int r = 1, sock_fd; 
    struct sockaddr_in serv; 
    char rcvmssg[50]; 
    
    bzero(&serv, sizeof(serv));
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0); 
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &r, sizeof(r));

    serv.sin_family = AF_INET; 
    serv.sin_port = htons(12345);
    serv.sin_addr.s_addr = INADDR_ANY; 

    bind(sock_fd, (struct sockaddr*)&serv, sizeof(serv));

    for(;;){
        bzero(rcvmssg, 50);
        recvfrom(sock_fd, rcvmssg, 100, 0, NULL, NULL);
        printf("received mssg: %s\n", rcvmssg);
    }

    close(sock_fd); 


}