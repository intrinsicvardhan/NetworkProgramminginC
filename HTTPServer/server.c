#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define PORT 8080

int main() {
    int server_fd, comm_fd;
    struct sockaddr_in serv;
    char server_response[1000];  // Use an array to store the response
    char time_string[100];

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(PORT);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0) {
        perror("Socket Creation Failed");
        exit(EXIT_FAILURE);
    }

    if (bind(server_fd, (struct sockaddr*)&serv, sizeof(serv)) < 0) {
        perror("In bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 10) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    int serv_len = sizeof(serv);

    for (;;) {
        if ((comm_fd = accept(server_fd, (struct sockaddr*)&serv, (socklen_t*)&serv_len)) < 0) {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        char buffer[30000] = {0};
        read(comm_fd, buffer, 30000);

        printf("%s", buffer);

        time_t raw_time;
        struct tm* time_info;

        time(&raw_time);
        time_info = localtime(&raw_time);

        strftime(time_string, sizeof(time_string), "Current Time: %d-%m-%Y %H:%M:%S\n", time_info);

        // Use snprintf to safely format the response
        snprintf(server_response, sizeof(server_response), "HTTP/1.1 200 OK\nContent-Type:text/html\n\n"
                                                            "<!DOCTYPE HTML><HTML><body>"
                                                            "<h1>Hello THERE</h1>%s</body></HTML>", time_string);

        write(comm_fd, server_response, strlen(server_response));
        close(comm_fd);
    }
    close(server_fd);


    return 0;
}
