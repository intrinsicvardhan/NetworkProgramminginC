#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define PORT 12345

int main() {
    int comm_fd, b = 1; 
    struct sockaddr_in serv; 
    char sendmssg[50], rcvmssg[50]; 


    bzero(&serv, sizeof(serv)); 
    bzero(sendmssg, 50);
    bzero(rcvmssg, 50);

    comm_fd = socket(AF_INET, SOCK_DGRAM, 0); 
    setsockopt(comm_fd, SOL_SOCKET, SO_BROADCAST, &b, sizeof(b));

    serv.sin_family = AF_INET; 
    serv.sin_addr.s_addr = inet_addr("255.255.255.255");
    serv.sin_port = htons(PORT); 


    for(;;) {   
        bzero(sendmssg, 50);
        bzero(rcvmssg, 50);


        printf("Send message? (yes/no)\n");
        fgets(sendmssg, 50, stdin);

        if(strstr(sendmssg, "no")!=NULL){
            printf("EXITING\n");
            sendto(comm_fd, sendmssg, strlen(sendmssg), 0, (struct sockaddr*)&serv, sizeof(serv));
            close(comm_fd);
            exit(0);
        }
        bzero(sendmssg, 50);
        printf("Enter message\n");
        fgets(sendmssg, 50, stdin);

        sendto(comm_fd, sendmssg, strlen(sendmssg), 0, (struct sockaddr*)&serv, sizeof(serv));
    }
    close(comm_fd);
    return 0;   
}