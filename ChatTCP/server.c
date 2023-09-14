#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  int listen_fd, comm_fd;
  char senddata[50], receivedata[50];
  struct sockaddr_in serv;

  // Initialize the send and receive buffers
  bzero(senddata, 50);
  bzero(receivedata, 50); 
  bzero((struct sockaddr*) &serv, sizeof(serv));
  // Set up the server address
  serv.sin_family = AF_INET;
  serv.sin_port = htons(8800);
  serv.sin_addr.s_addr = INADDR_ANY;

  // Create a socket
  listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_fd < 0) {
    perror("socket");
    exit(1);
  }

  // Bind the socket to the server address
  if (bind(listen_fd, (struct sockaddr *)&serv, sizeof(serv)) < 0) {
    perror("bind");
    exit(1);
  }

  // Listen for incoming connections
  listen(listen_fd, 10);

  // Accept an incoming connection
  comm_fd = accept(listen_fd, NULL, NULL);
  if (comm_fd < 0) {
    perror("accept");
    exit(1);
  }
while(1) {
  
  bzero(receivedata, 50); 
  bzero(senddata, 50);

  // Receive a message from the client
  if (recv(comm_fd, receivedata, sizeof(receivedata), 0) < 0) {
    perror("recv");
    exit(1);
  }

  // Print the message from the client
  printf("Message from client: %s\n", receivedata);

  printf("Send message: "); 
  fgets(senddata, sizeof(senddata), stdin);

  // Send the message back to the client
  send(comm_fd, senddata, strlen(receivedata), 0);
  if(strstr(senddata, "bye")!=NULL||strstr(receivedata, "bye")!=NULL){
   printf("Closing server...");
   break;
	 }	
}
  // Close the communication socket
  close(comm_fd);

  // Close the listening socket
  close(listen_fd);
  shutdown(comm_fd, SHUT_RDWR);
  shutdown(listen_fd, SHUT_RDWR);
  return 0;
}
