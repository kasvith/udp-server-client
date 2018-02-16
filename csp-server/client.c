/* Sample UDP client */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char**argv){
	int sockfd,n;
	struct sockaddr_in servaddr;
	char sendline[] = "Hello UDP server! This is UDP client";
	char recvline[1000];
	char* numoflines;

	if (argc != 2){
		printf("usage:%s <IP address>\n",argv[0]);
		return -1;
	}

	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(argv[1]);
	servaddr.sin_port=htons(4668);

	printf("%s", "Enter the number of sentences you want to send : ");
	scanf("%s", numoflines);

	sendto(sockfd,numoflines,strlen(numoflines),0,(struct sockaddr*)&servaddr,sizeof(servaddr));

	n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);

	recvline[n]=0;

	char ack[] = "ack";
	if(strcmp(ack, recvline) != 0){
		printf("Server refused : %s\n", recvline);
		return -1;
	}

	printf("Received: %s\n",recvline);
	return 0;
}