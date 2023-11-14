#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h> 
#include <stdlib.h>

int main() {
    int listen_fd, comm_fd, cli_len;
    char rcvmssg[50], sndmssg[50]; 
    struct sockaddr_in serv, cli; 
    
    bzero(rcvmssg, 50); 
    bzero(sndmssg, 50); 
    bzero(&serv, sizeof(serv)); 
    cli_len = sizeof(serv);

    serv.sin_family = AF_INET; 
    serv.sin_port = htons(6969); 
    serv.sin_addr.s_addr = INADDR_ANY; 

    listen_fd = socket(AF_INET, SOCK_STREAM, 0); 

    struct descriptor{
        short fd1,fd2;
    } D; 

    struct result { 
        short max;
    } M; 

    bind(listen_fd, (struct sockaddr*)&serv, sizeof(serv)); 

    listen(listen_fd, 10); 
    comm_fd = accept(listen_fd, (struct sockaddr*)&cli, &cli_len); 

    recv(comm_fd, &D, sizeof(D), 0);

    M.max = (D.fd1>D.fd2)?D.fd1:D.fd2; 

    printf("Operation done now sending back the descriptor\n"); 

    send(comm_fd, &M, sizeof(M), 0); 

    return 0;

}