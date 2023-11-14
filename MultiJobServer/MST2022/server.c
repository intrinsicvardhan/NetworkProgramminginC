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
    int listen_fd, comm_fd, max_fd, n_ready;
    char rcvmsg[50], sndmsg[50]; 
    struct sockaddr_in serv, cli; 
    socklen_t cli_len;

    bzero(rcvmsg, 50); 
    bzero(sndmsg, 50); 
    bzero(&serv, sizeof(serv)); 
    bzero(&cli, sizeof(cli)); 

    serv.sin_family = AF_INET; 
    serv.sin_port = htons(6969); 
    serv.sin_addr.s_addr = INADDR_ANY; 

    // Create a socket for listening
    listen_fd = socket(AF_INET, SOCK_STREAM, 0); 
    if (listen_fd < 0) {
        perror("socket");
        exit(1);
    }

    // Bind the socket to the server address
    if (bind(listen_fd, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("bind");
        exit(1);
    }

    // Start listening for incoming connections
    if (listen(listen_fd, 2) < 0) { // Assuming a maximum of TWO clients
        perror("listen");
        exit(1);
    }

    max_fd = listen_fd + 1; // The maximum file descriptor to monitor

    fd_set r_set; 
    FD_ZERO(&r_set); 
    FD_SET(listen_fd, &r_set);

    printf("Server is waiting for connections...\n");

    while (1) {
        cli_len = sizeof(cli);
        n_ready = select(max_fd, &r_set, NULL, NULL, NULL); 

        if (n_ready < 0) {
            perror("select"); 
            exit(1);
        }

        if (FD_ISSET(listen_fd, &r_set)) {
            // Accept a new connection
            comm_fd = accept(listen_fd, (struct sockaddr *)&cli, &cli_len);

            if (comm_fd < 0) {
                perror("accept");
                exit(1);
            }

            printf("Accepted connection from %s:%d\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port));

            // Read the string from the client
            ssize_t bytes_received = recv(comm_fd, rcvmsg, sizeof(rcvmsg), 0);
            if (bytes_received <= 0) {
                perror("recv");
                close(comm_fd);
                continue;
            }

            rcvmsg[bytes_received] = '\0'; // Null-terminate the received string
            printf("Message received: %s\n", rcvmsg);

            int n = strlen(rcvmsg) -1;

            // Send the length back to the client
            ssize_t bytes_sent = send(comm_fd, &n, sizeof(n), 0);
            if (bytes_sent < 0) {
                perror("send");
            }

            // Close the client socket
            close(comm_fd);

            // Check if the server should continue
            printf("Continue? (yes/no): ");
            fgets(sndmsg, sizeof(sndmsg), stdin);
            if (strstr(sndmsg, "no") != NULL) {
                printf("CLOSING...\n");
                close(listen_fd);
                exit(0);
            }
        }
    }

    return 0;
}
