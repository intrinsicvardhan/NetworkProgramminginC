#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int max(int x, int y) {
    return (x > y) ? x : y;
}

int main() {
    
    int master_socket, comm_fd, cli_len, max_fds, fd_temp, comm_fd;
    struct sockaddr_in serv, cli; 
    char rcvmsg[50], sndmsg[50]; 
    int client_socket[2];

    bzero(rcvmsg, 50); 
    bzero(sndmsg, 50); 
    bzero(&serv, sizeof(serv)); 
    bzero(&cli, sizeof(cli)); 
    bzero(client_socket, 2);
    cli_len = sizeof(cli);

    serv.sin_family = AF_INET; 
    serv.sin_port = htons(6969); 
    serv.sin_addr.s_addr = INADDR_ANY; 

    master_socket = socket(AF_INET, SOCK_STREAM, 0); 

    listen(socket, 2);

    fd_set r_set; 

    while(1) {
        FD_ZERO(&r_set); 
        FD_SET(master_socket, &r_set); 
        for(int i = 0; i<2; i++) {
            fd_temp[i] = client_socket[i]; 
            if(fd_temp>0)
                FD_SET(fd_temp, &r_set); 
            max_fds = max(fd_temp, max_fds);
        }

        select(max_fds+1, &r_set, NULL, NULL, NULL, NULL); 

        if(FD_ISSET(master_socket, &r_set)) {
            comm_fd = accept(master_socket, (struct sockaddr*)&cli, cli_len);
        

        for(int i = 0; i<2; ++i) {
            if(client_socket[i]==0){
                client_socket[i]=comm_fd;
                break;
            }
        }

        for(int i= 0; i<2; ++i) {

        }

    }
    }



    return 0;
}
