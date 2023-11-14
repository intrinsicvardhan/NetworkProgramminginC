#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() { 
    int listen_fd, comm_fd; 
    char receivemssg[50], sendmssg[50]; 
    struct sockaddr_in serv; 

    bzero(receivemssg, 50); 
    bzero(sendmssg, 50); 
    bzero(&serv, sizeof(serv)); 
    
    serv.sin_family = AF_INET; 
    serv.sin_port = htons(6969); 
    serv.sin_addr.s_addr = INADDR_ANY;

    listen_fd = socket(AF_INET, SOCK_STREAM, 0); 

    bind(listen_fd, (struct sockaddr*)&serv, sizeof(serv));

    listen(listen_fd, 2); 

    comm_fd = accept(listen_fd, (struct sockaddr*)NULL, NULL); 

    recv(comm_fd, receivemssg, sizeof(receivemssg), 0); 
    
    printf("String received: %s", receivemssg);

    int n = strlen(receivemssg); 


    send(comm_fd, &n, sizeof(n), 0);

    close(comm_fd); 
    close(listen_fd); 

    return 0; 

}