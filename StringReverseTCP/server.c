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
    struct sockaddr_in serv; 
    char rcvmsg[50], sndmsg[50]; 

    bzero(rcvmsg, 50); 
    bzero(sndmsg, 50); 
    bzero(&serv, sizeof(serv)); 

    serv.sin_family = AF_INET; 
    serv.sin_port = htons(6969); 
    serv.sin_addr.s_addr = htonl(INADDR_ANY); 

    listen_fd = socket(AF_INET, SOCK_STREAM, 0);

    listen(listen_fd, 10); 

    
}