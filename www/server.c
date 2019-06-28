#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include <stdlib.h>
#include<stdlib.h>
#include<stdio.h>
#define BUF_SIZE 256
#include<string.h>



void DieWithError(char *errorMessage){
	perror(errorMessage);
	exit(1);
}
void commun(int sock){
	char buf[BUF_SIZE];
	int len_r;
           char  *message ="���Ԃ���-��";
	
	if ((len_r=recv(sock, buf, BUF_SIZE,  0)) <= 0)                                    /***huleen avagch***/
	         DieWithError("recv() failed");
	
	buf[len_r]='\0';
	printf("%s\n",buf);
	
	if (send(sock, message, strlen(message), 0)!= strlen(message))
	         DieWithError("send() sent a message of unexpected bytes");
}
int main (int argc, char *argv){
	

	struct sockaddr_in clientAddress;
	unsigned int szClientAddr;
	int cliSock;
	
	int servSock = socket(PF_INET, SOCK_STREAM, 0);
	if (servSock < 0)
	DieWithError("socket() failed");

	struct sockaddr_in servAddress;

	servAddress.sin_family        =AF_INET;
	servAddress.sin_port          =htons(80);
	servAddress.sin_addr.s_addr   =htonl(INADDR_ANY);

	bind(servSock, (struct sockaddr*)&servAddress,sizeof(servAddress));

	listen(servSock,5);

	while(1){
		szClientAddr=sizeof(clientAddress);
	    cliSock=accept(servSock,(struct sockaddr*)&clientAddress,&szClientAddr);
	    commun(cliSock);
		close(cliSock);
    }
	close(servSock);
	return 0;
}