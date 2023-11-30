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
    struct ip_mreq mreq;
    
    // bzero(&serv, sizeof(serv));
    // sock_fd = socket(AF_INET, SOCK_DGRAM, 0); 
    // setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &r, sizeof(r));

    // serv.sin_family = AF_INET; 
    // serv.sin_port = htons(12345);
    // serv.sin_addr.s_addr = INADDR_ANY; 

    

    serv.sin_family = AF_INET;
    serv.sin_port = htons(12345);
    serv.sin_addr.s_addr = inet_addr("224.1.1.5"); //group value of the ip address


    bzero(&serv, sizeof(serv));
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &r, sizeof(r));

    // setsockopt(sock_fd, SOL_SOCKET, SO_BROADCAST, &b, sizeof(b)); no need in multicasting

    bind(sock_fd, (struct sockaddr*)&serv, sizeof(serv));


    mreq.imr_multiaddr.s_addr = inet_addr("224.1.1.5"); //creating nthe multicasting group
    mreq.imr_interface.s_addr = INADDR_ANY;
    setsockopt(sock_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
    

    for(;;){
        bzero(rcvmssg, 50);
        recvfrom(sock_fd, rcvmssg, 100, 0, NULL, NULL);
        printf("received mssg: %s\n", rcvmssg);

    }

    close(sock_fd); 


}