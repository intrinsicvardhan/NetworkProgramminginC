#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int count_vowels(char str[],int size) {
	int count = 0; 
	char vowels[5] = {'a', 'e' , 'i', 'o', 'u'};
	for(int i =0; i<size; ++i) {
		for(int j = 0; j<5; ++j) {
			if(vowels[j] == str[i] ) {
				count++; 
				break;
			}
		}
	}
	return count;
}
	

int main() {
	char senddata[50], receivedata[50], number[50]; 
	int listen_fd, comm_fd , count; 
	struct sockaddr_in serv; 

	bzero(senddata, 50); 
	bzero(receivedata,50); 
	bzero(&serv, sizeof(serv)); 
	
	listen_fd = socket(AF_INET, SOCK_STREAM, 0); 
	if(listen_fd<0) {
		perror("SOCKET CREATION FAILED");
		exit(1); 	
	}

	serv.sin_family = AF_INET; 
	serv.sin_port = htons(12345); 
	serv.sin_addr.s_addr = INADDR_ANY; 

	if(bind(listen_fd, (struct sockaddr *) &serv, sizeof(serv))<0){
		perror("BIND FAILED!");
		exit(1);
	}
		

	listen(listen_fd, 10); 

	comm_fd = accept(listen_fd, NULL, NULL); 
	
	recv(comm_fd, receivedata, 100,0);
	printf("Received message is: %s", receivedata); 
	count =  count_vowels(receivedata, strlen(receivedata));
	printf("Count = %d", count);
	sprintf(number, "%d", count);
	send(comm_fd,number,strlen(number), 0); 

	close(listen_fd); 
	close(comm_fd); 
	shutdown(listen_fd, SHUT_RDWR); 
	shutdown(comm_fd, SHUT_RDWR); 
	return 0;
	}
	
