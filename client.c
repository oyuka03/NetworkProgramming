#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>       /*** socket kansuugateigisareteiru***/
int main(int arg,char*argv){

	int sock=socket(PF_INET,SOCK_STREAM,0);
	
	struct sockaddr_in target;
	
	target.sin_family=AF_INET;
	target.sin_addr.s_addr=inet_addr("10.13.64.20"); /***hoid heseg ni@•ÏŠ·***/
	target.sin_port=htons(10001);
	
	connect(sock,(struct sockaddr*)&target,sizeof(target));
	
	close(sock);	
    return 0;
}