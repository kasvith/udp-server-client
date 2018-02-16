/* Sample UDP server */
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void uppercase(char * temp) {
  char* st;
  st = strtok(temp,":");

  // Convert to upper case
  char *s = st;
  while (*s) {
    *s = toupper((unsigned char) *s);
    s++;
  }

}

int main(int argc, char**argv){
	int sockfd,n;
	struct sockaddr_in servaddr, cliaddr;
	socklen_t len;
	char mesg[1000];
	char* banner = "Hello UDP client! This is UDP server";
	char* ack = "ack";
	int numoflines = 0;
	
	sockfd=socket(AF_INET,SOCK_DGRAM,0);	//create a socket
	
	servaddr.sin_family = AF_INET;	//address family	
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);	//IP address in the network byte order
	servaddr.sin_port = htons(4358);
	
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	len = sizeof(cliaddr);

	while(1){
		n=recvfrom(sockfd,mesg,1000,0,(struct sockaddr*)&cliaddr,&len);
		mesg[n] = 0;
		numoflines = atoi(mesg);

		sendto(sockfd,ack, strlen(ack),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
		
		printf("Waiting %s times\n",mesg);

		while(numoflines > 0){
			char msg[1000];
			n=recvfrom(sockfd,msg,1000,0,(struct sockaddr*)&cliaddr,&len);
			uppercase(msg);
			sendto(sockfd,msg, strlen(msg),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
			numoflines--;
		}
	}
	return 0;
}