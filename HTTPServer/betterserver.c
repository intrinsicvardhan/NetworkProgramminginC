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
    char server_response[1000];

    serv.sin_family = AF_INET; 
    serv.sin_addr.s_addr = INADDR_ANY; 
    serv.sin_port = htons(PORT);

    server_fd = socket(AF_INET, SOCK_STREAM, 0); 

    bind(server_fd, (struct sockaddr*)&serv, sizeof(serv)); 

    listen(server_fd, 10);

    int serv_len = sizeof(serv); 

    for(;;) {
        comm_fd = accept(server_fd, (struct sockaddr*)&serv, (socklen_t*)&serv_len); 

        char buffer[3000] = {0}; 
        read(comm_fd, buffer, 30000); 

        printf("%s", buffer); 

        time_t raw_time; //time_t
        struct tm* time_info; //

    }
}