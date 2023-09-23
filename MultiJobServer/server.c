#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

int max(int x, int y) {
    return (x>y)?x:y;
}

int main() {
    int listen_fd, udp_fd, nready, comm_fd, max_clients;
    char rcvmsg[50], sndmsg[50]; 
    struct sockaddr_in serv, cli;
    socklen_t len;

    bzero(rcvmsg, 50); 
    bzero(sndmsg, 50); 
    bzero(&serv, sizeof(serv)); 

    serv.sin_family = AF_INET; 
    serv.sin_port = htons(6969); 
    serv.sin_addr.s_addr = INADDR_ANY; 

    listen_fd = socket(AF_INET, SOCK_STREAM, 0); 
    udp_fd = socket(AF_INET, SOCK_DGRAM, 0); 
    
    bind(listen_fd, (struct sockaddr *)&serv, sizeof(serv)); 
    bind(udp_fd, (struct sockaddr*)&serv, sizeof(serv)); 

    listen(listen_fd, 10);

    fd_set set; 
    FD_ZERO(&set); 

    max_clients = max(listen_fd, udp_fd)+1; 
    for(;;) {
        FD_SET(udp_fd, &set); 
        FD_SET(listen_fd, &set); 
        
        nready = select(max_clients, &set, NULL, NULL, NULL); //null for write fd, null for except array as well as time
        
        //if tcp socket is readable then handle
        //it by accepting the connection
        if(FD_ISSET(listen_fd, &set)) {
            len = sizeof(cli);
            comm_fd = accept(listen_fd, (struct sockaddr*)&cli, &len);
            printf("TCP Connection accepted\n");
            while(1) {
                bzero(rcvmsg, 50); 
                read(comm_fd, rcvmsg, sizeof(rcvmsg));
                printf("Message received: %s\n", rcvmsg); 
                printf("Send Message: "); 
                fgets(sndmsg, sizeof(sndmsg),stdin); 
                write(comm_fd, sndmsg, strlen(sndmsg));
            }
            close(comm_fd);
            close(udp_fd);
            exit(0);
        }

        if(FD_ISSET(udp_fd, &set)) {
            len = sizeof(cli); 
            bzero(rcvmsg, 50); 
            recvfrom(udp_fd, rcvmsg, sizeof(rcvmsg), 0, (struct sockaddr*)&cli, &len);
            printf("Message received: %s\n", rcvmsg); 
            fgets(sndmsg, sizeof(sndmsg), stdin); 
            sendto(udp_fd, sndmsg, strlen(sndmsg), 0, (struct sockaddr*)&cli, len);
            close(udp_fd); 
            close(comm_fd);
            exit(0);
        }
        
        
    }
}