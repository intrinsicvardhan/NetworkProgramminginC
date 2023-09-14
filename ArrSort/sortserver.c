#include <sys/socket.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void bubble_sort(int arr[] , int size) {
	for(int i = 0; i<size;++i) {
		for(int j=0; j <size-i-1; ++j) {
			if(arr[j]>arr[j+1]) {
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
				}
		}
	}
}

int convert_to_int(char arr[10]) {
	return atoi(arr);  //ascii to integer value
}
//sprintf to use convert int to a

int main() {
	int sock_id, comm_fd, count ;
	char str[10], send_str[10];
	int arr[4];
	struct sockaddr_in serv; 

	sock_id = socket(AF_INET,SOCK_STREAM,0);
	
	bzero(str,10);
	bzero(&serv, sizeof(serv));
	bzero(arr,10);
	
	serv.sin_family = AF_INET;
	serv.sin_port = htons(8001); 
	serv.sin_addr.s_addr =  htonl(INADDR_ANY);
	//bind the address and port
	bind(sock_id, (struct sockaddr*) &serv, sizeof(serv));
	
	//listen
	listen(sock_id, 10);
	
	//initialize count 
	count = 0;

	//accept system call
	comm_fd = accept(sock_id, (struct sockaddr*) NULL, NULL);
	//receive from the client
	bzero(arr,10);
	bzero(str, 10);  
	recv(comm_fd, str,sizeof(str) ,0);
	printf("Number sent by client: %s", str); 
	arr[count] =  convert_to_int(str);
	count = 1; 
	while(count!=4) {
		bzero(str, 10);
		recv(comm_fd, str, sizeof(str), 0);
		printf("\nNumber sent by client: %s", str); 
		arr[count] = convert_to_int(str);
		count++;
	}
	printf("\n");
	bubble_sort(arr, 4);
	printf("Following is the sorted array\n");
	for(int i = 0; i<4; i++) {
		printf("%d\t", arr[i]); 
	}
	//sending back the sorted array
	for(int i = 0; i<4; ++i) {
		bzero(send_str, 0);
		sprintf(send_str, "%d", arr[i]);
		printf("Sending %s\n", send_str);
		send(comm_fd, send_str, sizeof(send_str), 0);
	}
	printf("\nClosing server");
	close(sock_id); 
	close(comm_fd);
	shutdown(sock_id, SHUT_RDWR); 
	shutdown(comm_fd, SHUT_RDWR);
	return 0;
	}

