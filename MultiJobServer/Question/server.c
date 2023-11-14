/*You are tasked with 
implementing a simple 
server program that can 
handle multiple client 
connections concurrently. 
Each connected client will s
end a message, and the server 
should receive and process 
these messages simultaneously. 
To achieve this, you need to use 
the select() system call for multiplexing.*/

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main() {
    int listen_fd, comm_fd, cli_len, max_fds;
    char rcvmsg[50], sendmsg[50]; 
    struct sockaddr_in serv, cli; 

    bzero(rcvmsg,50); 
    bzero(sendmsg,50);
    bzero(&serv, sizeof(serv)); 
    bzero(&cli, sizeof(cli)); 
    cli_len = sizeof(cli);

    serv.sin_family = AF_INET; 
    serv.sin_port = htons(6969); 
    serv.sin_addr.s_addr = htonl(INADDR_ANY);

    listen_fd = socket(AF_INET, SOCK_STREAM, 0); 
    bind(listen_fd, (struct sockaddr*)&serv, sizeof(serv)); 

    listen(listen_fd, 7); 

    max_fds = listen_fd+1;

    fd_set r_set; 
    FD_ZERO(&r_set);

    FD_SET(listen_fd, &r_set);

    while(1) {
        bzero(rcvmsg, 50); 
        bzero(sendmsg, 50);
        select(max_fds+1, &r_set, NULL, NULL, NULL);
        printf("Waiting for connections..\n");
        if(FD_ISSET(listen_fd, &r_set)){
            comm_fd = accept(listen_fd, (struct sockaddr*)&cli , &cli_len);
            printf("accepting connection from %s", inet_ntoa(cli.sin_addr)); 
            recv(comm_fd, rcvmsg, sizeof(rcvmsg), 0); 
            printf("Message received from client %s: %s", inet_ntoa(cli.sin_addr),rcvmsg); 
            printf("Enter :"); 
            fgets(sendmsg, sizeof(sendmsg), stdin);
            send(comm_fd, sendmsg, strlen(sendmsg), 0); 
        }
        if(strstr(sendmsg, "bye")!=NULL)
            exit(0);
        close(comm_fd);
    }
    return 0;
}