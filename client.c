#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>      
#include <string.h>                                                /*** socket kansuugateigisareteiru***/
#define BUF_SIZE 256

void DieWithError(char*errorMessage){
	perror(errorMessage);
	exit(1);
}

void commun(int sock){
	char buf[BUF_SIZE];
	int len_r;
	char*message="Hello serve03";
	if (send(sock,message,strlen(message),0)!= strlen(message))
	         DieWithError("send()sent a message of unexpected bytes");
	if ((len_r=recv(sock,buf,BUF_SIZE, 0)) <= 0)                                    /***huleen avagch***/
	         DieWithError("recv()failed");
	buf[len_r]='\0';
	
	
	printf("%s\n",buf);
}


int main(int argc, char**argv){
	
	if (argc != 3)
	DieWithError("argument is not available");
	
	char *server_ippadr = argv[1]; //"10.13.64.20";
	int server_port = atoi(argv[2]);
	
	int sock=socket(PF_INET,SOCK_STREAM,0);
	if (sock < 0)
	   DieWithError("socket()failed");
	
	struct sockaddr_in target;
	target.sin_family=AF_INET;
	target.sin_addr.s_addr=inet_addr(server_ippadr);       /***hoid heseg ni　変換***/
	target.sin_port=htons(server_port);
	
	if (connect(sock,(struct sockaddr*)&target,sizeof(target)) < 0)
		DieWithError("connect()failed");
	
	commun(sock);
	
	close(sock);	
    return 0;
}
