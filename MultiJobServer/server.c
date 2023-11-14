#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int max(int x, int y) {
    return (x > y) ? x : y;
}

int main() {
    int listen_fd, udp_fd, max_fd, nready, comm_fd;
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
    bind(udp_fd, (struct sockaddr *)&serv, sizeof(serv));

    listen(listen_fd, 5); // Assuming a maximum of 5 pending TCP connections

    max_fd = max(listen_fd, udp_fd) + 1;

    for (;;) {
        fd_set set; //create a set of file descriptors
        FD_ZERO(&set); // Zero out the file descriptor array
        FD_SET(udp_fd, &set); //Set the udp_fd into the file descriptors array
        FD_SET(listen_fd, &set); //Set the listen_fd into the file descriptor array

        nready = select(max_fd, &set, NULL, NULL, NULL); //nready is the value select returns when any of the fds get edited

        if (nready < 0) { //if nready<0 not a good sign
            perror("select"); 
            exit(1);
        }

        if (FD_ISSET(listen_fd, &set)) { //FD_ISSET returns non zero value if the file descriptor present in the set is ready for the specified operation
            len = sizeof(cli);
            comm_fd = accept(listen_fd, (struct sockaddr *)&cli, &len);
            printf("TCP Connection accepted\n");

            while (1) {
                bzero(rcvmsg, 50);
                printf("Waiting for TCP message...\n");
                int bytesRead = read(comm_fd, rcvmsg, sizeof(rcvmsg));

                if (bytesRead <= 0) {
                    printf("TCP Connection closed\n");
                    close(comm_fd);
                    break;
                }

                printf("TCP Message received: %s\n", rcvmsg);
                printf("Send Message: ");
                fgets(sndmsg, sizeof(sndmsg), stdin);
                write(comm_fd, sndmsg, strlen(sndmsg));
            }
        }

        if (FD_ISSET(udp_fd, &set)) {
            len = sizeof(cli);
            bzero(rcvmsg, 50);
            printf("Waiting for UDP message...\n");
            recvfrom(udp_fd, rcvmsg, sizeof(rcvmsg), 0, (struct sockaddr *)&cli, &len);

            printf("UDP Message received: %s\n", rcvmsg);
            printf("Send Message: ");
            fgets(sndmsg, sizeof(sndmsg), stdin);
            sendto(udp_fd, sndmsg, strlen(sndmsg), 0, (struct sockaddr *)&cli, len);
        }
    }
}
