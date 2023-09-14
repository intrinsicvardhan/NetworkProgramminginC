#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int main() {
	int sock_id; 
	char arr[10], sortedarr[10];
	struct sockaddr_in serv; 

	sock_id = socket(AF_INET,SOCK_STREAM,0);
	
	bzero(arr,10);
	bzero(&serv, sizeof(serv));
	bzero(sortedarr, 10);
	
	serv.sin_family = AF_INET;
	serv.sin_port = htons(8001); 
	serv.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	
	connect(sock_id, (struct sockaddr*)&serv, sizeof(serv));

	bzero(arr,10); 
	printf("Enter number one by one : "); 
	fgets(arr,10,stdin); 
	send(sock_id, arr, 1, 0);
	int count = 1; 
	while(count!=4) {
		printf("Enter another number "); 
		bzero(arr, 10); 
		fgets(arr, sizeof(arr), stdin); 
		send(sock_id, arr, sizeof(arr),0); 
		count++;
	}
	printf("Array Sent", arr);
	
	//Receive the sorted array
	count = 0; 
	printf("Following is the sorted array\n");
	while(count!=4) {
		recv(sock_id, sortedarr, sizeof(sortedarr), 0);
		printf("%s\t", sortedarr);
		count++; 
	}
	close(sock_id); 
	shutdown(sock_id, SHUT_RDWR); 
	return 0;
	}
