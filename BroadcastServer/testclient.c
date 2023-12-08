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
    int comm_fd, r = 1; 
    struct sockaddr_in serv, cli; 
    char rcvmessg[50];

    bzero(&serv, sizeof(serv));
    bzero(rcvmessg, 50);
    bzero(&cli, sizeof(cli));

    serv.sin_family = AF_INET; 
    serv.sin_addr.s_addr = INADDR_ANY; 
    serv.sin_port = htons(PORT);

    comm_fd = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt(comm_fd, SOL_SOCKET, SO_REUSEADDR, &r, sizeof(r));

    bind(comm_fd, (struct sockaddr*)&serv, sizeof(serv));

    int cli_len = sizeof(cli);

    for(;;) {
        bzero(rcvmessg, 50);
        recvfrom(comm_fd, rcvmessg, sizeof(rcvmessg), 0, (struct sockaddr*)&cli, (socklen_t*)&cli_len);
        if(strstr(rcvmessg, "no")!=NULL){
            printf("Server closed the connection...\n");
            close(comm_fd);
            exit(0);
        }
        printf("received message: %s\n", rcvmessg);
    }
    close(comm_fd);
    return 0;
}