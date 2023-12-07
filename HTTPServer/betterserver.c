#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define PORT 8081

int main() {
    int server_fd, comm_fd;
    struct sockaddr_in serv; 
    char server_response[1000], time_string[1000];

    serv.sin_family = AF_INET; 
    serv.sin_addr.s_addr = INADDR_ANY; 
    serv.sin_port = htons(PORT); 

    server_fd = socket(AF_INET, SOCK_STREAM, 0); 

    bind(server_fd, (struct sockaddr*)&serv, sizeof(serv));
    listen(server_fd, 10);
    socklen_t serv_len = sizeof(serv);

    for(;;) {
        comm_fd = accept(server_fd, (struct sockaddr *)&serv, (socklen_t*)&serv_len); //accept the connection request

        char buffer[30000] = {0}; 

        read(comm_fd, buffer, sizeof(buffer));

        time_t raw_time; 
        struct tm* time_info; 

        time(&raw_time);
        time_info = localtime(&raw_time);

        char* time_str = asctime(time_info);

        snprintf(server_response, sizeof(server_response), "HTTP/1.1 200 OK\nContent-Type:text/html\n\n"
                                                           "<!DOCTYPE HTML><HTML><body>"
                                                           "<h1>Hello!!!!</h1><script>"
                                                           "setInterval(location.reload, 5000);</script>"
                                                           "%s</body></HTML>", time_str);
    }
    close(server_fd);
    return 0;

}

