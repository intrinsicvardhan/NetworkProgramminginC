#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main() {
    int b = 1, sock_fd; 
    struct sockaddr_in serv; 
    char sendmssg[50], str2[10];

    serv.sin_family = AF_INET;
    serv.sin_port = htons(12345);
    serv.sin_addr.s_addr = inet_addr("224.1.1.5"); //group value of the ip address

    bzero(&serv, sizeof(serv));
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0); 
    // setsockopt(sock_fd, SOL_SOCKET, SO_BROADCAST, &b, sizeof(b)); no need in multicasting
    struct ip_mreq mreq; 
    mreq.imr_multiaddr.s_addr = inet_addr("224.1.1.5"); //creating nthe multitasking group
    mreq.imr_interface.s_addr = INADDR_ANY;
    setsockopt(sock_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));
    
    while(1) {
        bzero(str2, sizeof(str2));
        bzero(sendmssg, sizeof(sendmssg));
        printf("Do you want to send the data or not? (yes/no)\n");
        fgets(str2, 10, stdin);
        if(strstr(str2, "no")!=NULL){
            printf("Exiting..\n");
            exit(0);
        }
        printf("Enter messg\n");
        fgets(sendmssg, 50, stdin);
        sendto(sock_fd, sendmssg, strlen(sendmssg), 0, (struct sockaddr*)&serv, sizeof(serv));

    }
    close(sock_fd);
    return 0; 
}