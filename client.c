#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 256
#define MONEY_DIGIT_SIZE 10

void DieWithError(char *);

int prepare_server_socket(int);
void commuun(int)

	void DieWithError(char *errorMessage)
{
	perror(errorMessage);
	exit(1);
}

int prepare_server_socket(int port)
{
	int servSock = socket(PF_INET, SOCK_STREAM, 0);

	struct sockaddr_in servAddress;

	servAddress.sin_family = PF_INET;
	servAddress.sin_port = (in_port_t)htons(80);
	servAddress.sin_addr.s_addr = htonl(INADDR_ANY);
}

int main(int argc, char *argv)
{
	struct sockaddr_in clientAddress;
	unsigned int szClientAddr;
	int cliSock;

	int serveSock = prepare_server_socket(10001);

	listen(serveSock, 5);

	while (1)
	{
		szClientAddr = sizeof(clientAddress);
		cliSock = accept(serveSock, (struct sockaddr *)&clientAddress, &szClientAddr);

		commun(cliSock);

		close(cliSock);
	}
