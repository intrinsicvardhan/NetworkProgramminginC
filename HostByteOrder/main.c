#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <string.h>
//SO_LINGER socket option is used to control how the close() function operatoes for a protocol such as TCP
//By default, close() returns immediately, but if there is any data still remains the system will 
//try to delivery the data to the peer. 

//The SO_LINGER socket option takes al inger structure as its argument. The linger structure has two members 
//I_onoff:  a flag that indicates whether the SO_LINGER option is enabled or disabled
//I_linger: A timeout value, in seconds




int main() {
	printf("%d", 101001);
	return 0;
}
	
		
//Need a method to control the sockets
