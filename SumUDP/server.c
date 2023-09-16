#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() { 
	int sock_id, client_len; 
	char sendmessage[50], receivemessage[50]; 
	struct sockaddr_in serv, cli; 

	bzero(sendmessage,50); 
	bzero(receivemessage,50); 
	bzero(&serv, sizeof(serv)); 
	bzero(&cli, sizeof(cli)); 
	client_len = sizeof(cli); 

	sock_id = socket(AF_INET, SOCK_DGRAM, 0); 
	
	serv.sin_family = AF_INET; 
	serv.sin_port = htons(21400); 
	serv.sin_addr.s_addr = INADDR_ANY;

	bind(sock_id, (struct sockaddr*) &serv, sizeof(serv)); 

	int arr[2]; 

	for(int i = 0; i<2; ++i) {
		bzero(receivemessage,50);
		recvfrom(sock_id, receivemessage, sizeof(receivemessage), 0, (struct sockaddr*)&cli, &client_len);
		arr[i] = atoi(receivemessage); 
		}
		int sum = arr[0]+arr[1]; 
		printf("The sum of the given numbers is :%d", sum);
		sprintf(sendmessage, "%d", sum); 
	
		sendto(sock_id, sendmessage, strlen(sendmessage), 0, (struct sockaddr*)&cli, client_len); 
		
		close(sock_id); 
		shutdown(sock_id, SHUT_RDWR); 

		return 0; 
	}
