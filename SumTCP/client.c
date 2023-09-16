#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	int sock_id; 
	char sendmessage[50], receivemessage[50]; 
	struct sockaddr_in serv; 

	bzero(sendmessage, 50); 
	bzero(receivemessage, 50); 
	bzero(&serv, sizeof(serv)); 

	sock_id = socket(AF_INET, SOCK_STREAM, 0); 
	
	serv.sin_family = AF_INET; 
	serv.sin_port = htons(21400); 
	serv.sin_addr.s_addr = inet_addr("127.0.0.1"); 

	connect(sock_id, (struct sockaddr*)&serv, sizeof(serv)); 

	for(int i = 0; i<2; ++i) {
		bzero(sendmessage, 50);
		printf("Enter a number: ");
		fgets(sendmessage, sizeof(sendmessage), stdin);
		send(sock_id, sendmessage, strlen(sendmessage), 0);
		}
	
	recv(sock_id, receivemessage, sizeof(receivemessage), 0); 
	printf("\nThe resulting sum is: %s", receivemessage);

	close(sock_id); 
	shutdown(sock_id, SHUT_RDWR); 

	return 0; 
}
