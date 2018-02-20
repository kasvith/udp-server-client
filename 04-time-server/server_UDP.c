/* Sample UDP server */
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char**argv){
	int sockfd,n;
	struct sockaddr_in servaddr, cliaddr;
	socklen_t len;
	char mesg[1000];
	
	sockfd=socket(AF_INET,SOCK_DGRAM,0);	//create a socket
	
	servaddr.sin_family = AF_INET;	//address family	
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);	//IP address in the network byte order
	servaddr.sin_port=htons(3776);
	
	bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	len = sizeof(cliaddr);

	n=recvfrom(sockfd,mesg,1000,0,(struct sockaddr*)&cliaddr,&len);

	while(1){
		time_t current_time;
		struct tm * time_info;
		char timeString[9];  // space for "HH:MM:SS\0"

		time(&current_time);
		time_info = localtime(&current_time);

		strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);
		printf("Sending : %s\n", timeString);
		sendto(sockfd,timeString,9,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
		sleep(1);
	}
	return 0;
}