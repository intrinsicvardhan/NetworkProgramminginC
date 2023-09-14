#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX 100

int main() {
    int sock, serv_len;
    struct sockaddr_in serv;
    char strsend[MAX], strrecv[MAX];
    
    bzero(strsend, MAX);
    bzero(strrecv, MAX);
    bzero(&serv, sizeof(serv));

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    serv.sin_family = AF_INET;
    serv.sin_port = htons(21400);
    serv.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_len = sizeof(serv);

    while (1) {
        bzero(strsend, MAX);
        bzero(strrecv, MAX);

        int n = 0;
        printf("Enter a message to send: ");
        while ((strsend[n++] = getchar()) != '\n');
        
        sendto(sock, strsend, strlen(strsend), 0, (struct sockaddr*) &serv, serv_len);
        if (strstr(strsend, "bye") != NULL) {
            printf("Closing client...\n");
            break;
        }

        recvfrom(sock, strrecv, MAX, 0, (struct sockaddr*)&serv, &serv_len);
        printf("Received message is: %s", strrecv);
    }

    close(sock);
    shutdown(sock, SHUT_RDWR);
    return 0;
}
