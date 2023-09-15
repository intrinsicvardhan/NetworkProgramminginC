#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>

int main() {
	char senddata[50], receivedata[50]; 
	int sock_id; 
	struct sockaddr_in serv; 
	
	bzero(senddata,50); 
	bzero(receivedata,50); 
	bzero(&serv, sizeof(serv)); 

	serv.sin_family = AF_INET; 
	serv.sin_port = htons(12345); 
	serv.sin_addr.s_addr = inet_addr("127.0.0.1"); 

	sock_id = socket(AF_INET, SOCK_STREAM,0);
	
	connect(sock_id, (struct sockaddr*)&serv, sizeof(serv)); 

	printf("Enter the message: "); 
	fgets(senddata, sizeof(senddata), stdin); 
	send(sock_id,senddata, strlen(senddata), 0); 

	recv(sock_id, receivedata, 100, 0); 

	printf("Number of vowels in the string are: %s",receivedata); 
	
	close(sock_id); 
	shutdown(sock_id, SHUT_RDWR); 
	return 0; 
	}
