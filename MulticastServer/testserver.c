#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define PORT 6969

int main() {
    int sock_fd;
    struct sockaddr_in serv; 
    struct ip_mreq mreq; //ip_mreq is ip multicast request
    char sendmssg[50], recvmssg[50]; 

    bzero(&serv, sizeof(serv));
    bzero(&mreq, sizeof(mreq));
    bzero(sendmssg, 50);
    bzero(recvmssg, 50);

    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

    serv.sin_family = AF_INET; 
    serv.sin_port = htons(PORT);
    serv.sin_addr.s_addr = inet_addr("224.1.1.5");

    mreq.imr_multiaddr.s_addr = inet_addr("224.1.1.5");
    mreq.imr_interface.s_addr = INADDR_ANY;

    setsockopt(sock_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));

    for(;;) {
        bzero(sendmssg, 50);
        bzero(recvmssg, 50);

        printf("send message? (yes/no)");
        fgets(sendmssg, 50, stdin);
        if(strstr(sendmssg, "no")!=NULL){
            printf("EXITING.....");
            close(sock_fd);
            exit(0);
        }
        bzero(sendmssg, 50);
        printf("Enter message\t");
        fgets(sendmssg, 50, stdin);
        sendto(sock_fd, sendmssg, strlen(sendmssg),0, (struct sockaddr*)&serv,sizeof(serv)); 
    }
    close(sock_fd);
    return 0;
}