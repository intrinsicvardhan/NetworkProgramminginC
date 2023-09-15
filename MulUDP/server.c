#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

int main() {
	int sock_id, clientlen; 
	struct sockaddr_in serv, cli; 
	char sendmessage[50], receivemessage[50]; 
	int numbers[2]; 

	bzero(&serv, sizeof(serv));
	bzero(&cli, sizeof(cli)); 
	bzero(sendmessage, 50); 
	bzero(receivemessage,50); 

	sock_id = socket(AF_INET, SOCK_DGRAM, 0); 
	clientlen = sizeof(cli);

	serv.sin_family = AF_INET; 
	serv.sin_port = htons(21400); 
	serv.sin_addr.s_addr = INADDR_ANY; 

	bind(sock_id, (struct sockaddr*)&serv, sizeof(serv)); 
	
	for(int i = 0; i<2; ++i) {
		bzero(receivemessage, 50);
		recvfrom(sock_id, receivemessage, sizeof(receivemessage), 0, (struct sockaddr*)&cli, &clientlen);
		numbers[i] = atoi(receivemessage);
		}
	int multiplied = numbers[0]*numbers[1]; 
	
	sprintf(sendmessage, "%d", multiplied); 

	sendto(sock_id, sendmessage, strlen(sendmessage), 0, (struct sockaddr*)&cli, clientlen); 

	close(sock_id); 
	shutdown(sock_id, SHUT_RDWR); 
	return 0; 
	}
	
