/* Sample UDP client */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char**argv){
	int sockfd,n;
	struct sockaddr_in servaddr;
	char sendline[1000];
	char recvline[1000];
	char numoflines[1000];

	if (argc != 2){
		printf("usage:%s <IP address>\n",argv[0]);
		return -1;
	}

	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	
	bzero(&servaddr,sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(argv[1]);
	servaddr.sin_port=htons(4358);

	printf("%s", "Enter the number of sentences you want to send : ");
	scanf("%s", numoflines);

	sendto(sockfd,numoflines,strlen(numoflines),0,(struct sockaddr*)&servaddr,sizeof(servaddr));

	n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);

	recvline[n]=0;

	char ack[] = "ack";
	if(strcmp(ack, recvline) != 0){
		printf("Server refused\n");
		return -1;
	}

	printf("Type each sentence and press enter\n");
	int nn = atoi(numoflines);
	int i = 0;

	for (i = 0; i < nn; i++)
	{
		printf("Sentence %d : ", i+1);
		scanf("%s", sendline);
		sendto(sockfd,sendline,strlen(sendline),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
		n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);
	
		recvline[n]=0;

		printf("Uppercase : %s\n", recvline);
	}

	return 0;
}