#include <sys/types.h>
#include <sys/socket.h> 
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
  int sock_fd;
  char senddata[50], receivedata[50];
  struct sockaddr_in servaddr;

  // Create a socket
  sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_fd < 0) {
    perror("socket");
    exit(1);
  }

  // Zero out the send and receive buffers
  bzero(senddata, 50); 
  bzero(receivedata, 50);
  bzero((struct sockaddr*)&servaddr, sizeof(servaddr));

  // Set up the server address
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  servaddr.sin_port = htons(8800);

  // Connect to the server
  if (connect(sock_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    perror("connect");
    exit(1);
  }
while(1) {
  bzero(senddata, 50); 
  bzero(receivedata, 50); 
  // Get the user's input
  printf("Send Message: ");
  fgets(senddata, sizeof(senddata), stdin);

  // Send the user's input to the server
  if (send(sock_fd, senddata, strlen(senddata), 0) < 0) {
    perror("send");
    exit(1);
  }

  // Receive a response from the server
  if (recv(sock_fd, receivedata, sizeof(receivedata), 0) < 0) {
    perror("recv");
    exit(1);
  }

  // Print the response from the server
  printf("\nMessage from server: %s\n", receivedata);
  
  if((strstr(senddata, "bye")!=NULL) || (strstr(receivedata, "bye")!=NULL)) {
    printf("Closing client.."); 
    break; 
   }
}
  // Close the socket
  close(sock_fd);
  shutdown(sock_fd, SHUT_RDWR);
  return 0;
}
