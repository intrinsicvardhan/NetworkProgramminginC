#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PORT 6969

int main() {
    int sock_fd, r = 1; 
    struct sockaddr_in serv;
    struct ip_mreq mreq;
    char sendmssg[50], rcvmssg[50];

    bzero(&mreq, sizeof(mreq));
    bzero(&serv, sizeof(serv));
    bzero(sendmssg, 50);
    bzero(rcvmssg, 50);

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    serv.sin_family = AF_INET; 
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = INADDR_ANY;
    bind(sock_fd, (struct sockaddr*)&serv, sizeof(serv));

    mreq.imr_multiaddr.s_addr = inet_addr("224.1.1.5");
    mreq.imr_interface.s_addr = INADDR_ANY; 

    setsockopt(sock_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &r, sizeof(r));
    



    for(;;) {
        bzero(rcvmssg, 50);
        recvfrom(sock_fd, rcvmssg, sizeof(rcvmssg), 0, NULL, NULL);
        printf("received message: %s", rcvmssg);
    }
    close(sock_fd);

    
return 0;
  


}