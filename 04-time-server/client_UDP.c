/* Sample UDP client */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char**argv){
	int sockfd,n;
	struct sockaddr_in servaddr;
	char recvline[1000];

	if (argc != 2){
		printf("usage:%s <IP address>\n",argv[0]);
		return -1;
	}
	
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(argv[1]);
	servaddr.sin_port=htons(3776);

	while(1){
		n=recvfrom(sockfd,mesg,1000,0,(struct sockaddr*)&cliaddr,&len);
		mesg[n] = 0;
		puts(mesg);
	}

	
	return 0;
}