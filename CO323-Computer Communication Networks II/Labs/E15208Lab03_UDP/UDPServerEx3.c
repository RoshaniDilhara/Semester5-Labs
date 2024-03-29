/*
Comment are made by E/15/385
to make the code more understandable
*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc,char **argv){
	int sockfd,n;
	struct sockaddr_in serverAddress,clientAddress;
	socklen_t length;
	char message[1000];

	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	serverAddress.sin_family=AF_INET;
	serverAddress.sin_addr.s_addr=htonl(INADDR_ANY);
	serverAddress.sin_port=htons(32000);
	bind(sockfd,(struct sockaddr *)&serverAddress,sizeof(serverAddress));
	length=sizeof(clientAddress);

	n=recvfrom(sockfd,message,1000,0,(struct sockaddr*)&clientAddress,&length);
	message[n]=0;

	//recieve the number of sentences from client
	int noOfSentences=atoi(message);

	sendto(sockfd,"ack",n,0,(struct sockaddr*)&clientAddress,sizeof(clientAddress));
	printf("Recieved : %s\n",message);

	//send ack to client
	printf("Sent : ack\n");

	int i,j;
	i=0;
	while(i<noOfSentences){
		n=recvfrom(sockfd,message,1000,0,(struct sockaddr*)&clientAddress,&length);
		//receive number of sentences given
		message[n]=0;
		printf("Recieved : %s",message);

		//convert message to uppercase characters
		for(j=0;j<n;j++){
			message[j]=toupper(message[j]);
		}

		//send the uppercase sentence
		sendto(sockfd,message,n,0,(struct sockaddr*)&clientAddress,sizeof(clientAddress));
		printf("Sent : %s",message);
	i++;
	}

	return 0;
}
