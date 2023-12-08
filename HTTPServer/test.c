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
    int server_fd, comm_fd; 
    struct sockaddr_in serv, cli; 
    char server_response[1000];
    char* time_string; 

    bzero(&server_response, sizeof(server_response));
    bzero(&serv, sizeof(serv));
    bzero(&cli, sizeof(cli));

    serv.sin_family = AF_INET; 
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(PORT);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    bind(server_fd, (struct sockaddr*)&serv, sizeof(serv));

    listen(server_fd, 10); //queue is of 10

    int cli_len = sizeof(cli);

    for(;;) {
        comm_fd = accept(server_fd, (struct sockaddr*)&cli, (socklen_t*)&cli_len);

        char buffer[30000]; 
        bzero(&buffer, sizeof(buffer));

        read(comm_fd, buffer, sizeof(buffer));

        printf("%s", buffer);
        printf("Received request from %s:%d\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));

        snprintf(server_response, sizeof(server_response), "HTTP/1.1 200 OK\nContent-Type:text/html\n\n<!DOCTYPE HTML><html><body><h2>Connection Accepted</h2></body></html>");
        write(comm_fd, server_response, strlen(server_response));
        close(comm_fd);
    }
    close(server_fd);
    return 0;
}

