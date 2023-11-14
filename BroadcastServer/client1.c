#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int r = 1, sock_fd; 
    struct sockaddr_in serv; 
    char rcvmssg[50]; 
    
    bzero(&serv, sizeof(serv));
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0); 
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &r, sizeof(r));

    serv.sin_family = AF_INET; 
    serv.sin_port = htons(12345);
    serv.sin_addr.s_addr = INADDR_ANY; 

    int timeout_seconds = 10;
    time_t start_time, current_time;
    time(&start_time);

    for (;;) {
        bzero(rcvmssg, 50);
        ssize_t bytes_received = recvfrom(sock_fd, rcvmssg, sizeof(rcvmssg), 0, NULL, NULL);

        // if (bytes_received < 0) {
            time(&current_time);
            if (current_time - start_time >= timeout_seconds) {
                printf("No data received for %d seconds. Closing the socket.\n", timeout_seconds);
                close(sock_fd);
                exit(0);
            }
        // } else {
            printf("Received message: %s\n", rcvmssg);
            time(&start_time);  // Reset the timeout start time
        }
    }

    close(sock_fd); 

    return 0;
}
