/* TCP server */
/* E/15/208 */


#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char**argv){

int listenfd,connfd,n;
struct sockaddr_in servaddr,cliaddr;
socklen_t clilen;
//char* banner = "Hello TCP client! This is TCP server";
char buffer[1000];
char* file_size = "6000";

FILE *reqFile;

//open the requested file to read
reqFile = fopen("requested_file/serverfile.txt", "r");
    if (reqFile == NULL) {
        char* errorMsg = "error in opening the  file.\n";
        printf("%s", errorMsg);
     }

/* one socket is dedicated to listening */
listenfd=socket(AF_INET,SOCK_STREAM,0);

/* initialize a sockaddr_in struct with our own address information for
binding the socket */
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(32000);

/* binding */
bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
listen(listenfd,0);
clilen=sizeof(cliaddr);

/* accept the client with a different socket. */
connfd = accept(listenfd,(struct sockaddr *) &cliaddr, &clilen); 
// the uninitialized cliaddr variable is filled in with the

n = recvfrom(connfd,buffer,1000,0,(struct sockaddr *)&cliaddr,&clilen);
//information of the client by recvfrom function


buffer[n] = 0;
sendto(connfd,file_size,strlen(file_size),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
printf("Received:%s\n",buffer);

//read the file and send
while(fgets(buffer,1000,(FILE*)reqFile) != NULL){
  sendto(connfd,buffer,strlen(buffer),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
}

//close the file
fclose(reqFile);


return 0;
}