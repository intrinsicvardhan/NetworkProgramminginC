#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int listen_fd, comm_fd; 
	char sendmessage[50], receivemessage[50]; 
	struct sockaddr_in serv; 

	bzero(sendmessage, 50); 
	bzero(receivemessage,50); 
	bzero(&serv, sizeof(serv)); 

	listen_fd = socket(AF_INET, SOCK_STREAM, 0); 
	
	serv.sin_family = AF_INET; 
	serv.sin_port = htons(21400); 
	serv.sin_addr.s_addr = htonl(INADDR_ANY); 

	bind(listen_fd, (struct sockaddr*)&serv, sizeof(serv)); 
	
	listen(listen_fd, 10); 

	comm_fd = accept(listen_fd, NULL, NULL);
	
	int arr[2];
	for(int i = 0; i<2; ++i) {
		bzero(receivemessage,50); 
		recv(comm_fd, receivemessage, sizeof(receivemessage), 0); 
		arr[i] = atoi(receivemessage); 
		}
	int sum = arr[0] + arr[1]; 
	printf("The sum of the given numbers are %d", sum); 
	sprintf(sendmessage, "%d", sum);
	send(comm_fd, sendmessage, strlen(sendmessage), 0); 
	
	close(comm_fd); 
	close(listen_fd); 
	
	shutdown(comm_fd, SHUT_RDWR); 
	shutdown(listen_fd, SHUT_RDWR); 

	return 0; 
}

	
