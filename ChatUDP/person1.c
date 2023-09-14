#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX 100

int main() {
    int sock, clientlen;
    struct sockaddr_in serv, cli;
    char str[MAX], send_str[MAX];
    
    bzero(&serv, sizeof(serv)); // initializing the server struct to zeroes
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    serv.sin_family = AF_INET;
    serv.sin_port = htons(21400);
    serv.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr*)&serv, sizeof(serv)) < 0) {
        perror("Bind failed");
        return 1;
    }

    clientlen = sizeof(cli);

    while (1) {
        bzero(str, MAX);
        bzero(send_str, MAX);

        if (recvfrom(sock, str, MAX, 0, (struct sockaddr*)&cli, &clientlen) < 0) {
            perror("Receive failed");
            break;
        }

        char *client_ip = inet_ntoa(cli.sin_addr);
        printf("Received message from %s: %s\n", client_ip, str);

        int n = 0;
        printf("Enter a message to send: ");
        while ((send_str[n++] = getchar()) != '\n');

        if (strstr(send_str, "bye") != NULL) {
            sendto(sock, send_str, n, 0, (struct sockaddr*) &cli, clientlen);
            printf("Closing server...\n");
            break;
        }

        sendto(sock, send_str, n, 0, (struct sockaddr*) &cli, clientlen);
    }

    close(sock);
    shutdown(sock, SHUT_RDWR);
    return 0;
}

