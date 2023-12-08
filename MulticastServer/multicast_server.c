#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
int main()
{
int sock;
struct sockaddr_in serv;
struct ip_mreq mreq; //
char str1[100],str2[10];
char str3[3]="bye";
bzero(&serv,sizeof(serv));
sock=socket(AF_INET,SOCK_DGRAM,0);
serv.sin_family=AF_INET;
serv.sin_port=htons(12345);
serv.sin_addr.s_addr=inet_addr("224.1.1.5"); //setting the group id
mreq.imr_multiaddr.s_addr=inet_addr("224.1.1.5");
mreq.imr_interface.s_addr=INADDR_ANY;
setsockopt(sock,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq));

while(1)
{
printf("do you want to send data ");
fgets(str2,10,stdin);
if(strncmp(str2,"yes",3)==0)
{
bzero(str1,100);
printf("enter data: ");
fgets(str1,100,stdin);
sendto(sock,str1,strlen(str1),0,(struct sockaddr *)&serv,sizeof(serv));
}
else{
break;
}
}
close(sock);
}
