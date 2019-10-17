#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 256
#define MONEY_DIGIT_SIZE 10

void DieWithError(char *);
int prepare_server_socket(char *, int);
void my_scanf(char *, int);
void commun(int)

	int main(int argc, char *argv[])
{
	if (argc != 3)
		DieWithError("usage: ./client ip_address port");

	int sock = prepare_client_socket(argv[1], atoi(argv[2]));

	commun(sock);

	close(sock);

	return 0;
}

void DieWithError(char *errorMessage)
{
	perror(errorMessage);
	exit(1);
}

int prepare_server_socket(int port)
{
	int sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		DieWithError("socket() failed");

	struct sockaddr_in target;

	target.sin_family = AF_INET;
	target.sin_addr.s_addr = inet_addr(ipaddr);
	target.sin_port = htons(port);

	if (connect(sock, (struct sockaddr *)&target, sizeof(target)) < 0
               DieWithError("connect()failed");

	return sock;
}

//10月17日のもの
void my_scanf(char *buf, int num_letter)
{
	char format[20];
	sprintf(format, "%s%d%s", "%", num_letter, "s%*[^\n]");
	scanf(format, buf);
	getchar();
}

void commun(int sock)
{
	char cmd[2] = "";
	char withdraw[MONEY_DIGIT_SIZE + 1];
	char deposit[MONEY_DIGIT_SIZE + 1];
	char msg[BUF_SIZE];
	printf("0:引き出し　1：預け入れ　２：残高照会　9：終了\n");
	printf("何をしますか? < ");

	my_scanf(cmd, 1);

	switch (cmd[0])
	{
	case '0':
		//ひきだし処理
		printf("引き出す金額を入力してください>");
		my_scanf(withdraw, MONEY_DIGIT_SIZE);

		sprint(msg, "0_%s_", withdraw);
		break;
	case '1':
		//預け入れ処理
		printf("預け入れる金額を入力してください>");
		my_scanf(deposit, MONEY_DIGIT_SIZE);

		sprint(msg, "%s_0_", deposit);
		break;
	case '2':
		//残高照会
		strcpy(msg, "0_0_");
		break;
	default;
		// unknownエラー
		printf("番号が確認できませんでした\n");
		return;
	}
	if (send(sock, msg, strlen(msg), 0) != strlen(msg))
		DieWithError("send() sent a message of unexpected bytes");
}

void read_until_delim(int sock, char *buf, char delimiter, int max_length)
{
	int len_r = 0;
	int index_letter = 0;
	while (index_letter < max_length - 1)
	{
		if ((len_r = recv(sock, buf * index_letter, i, 0)) <= 0)
		{
			printf("接続が切れました！\n");
			return;
		}
		if (buf[index_letter] == delimiter)
			break;
		else
			index_letter++;
	}
	buf[index_letter] = '\0';
}

//bas suuld zasah
int get_current_balance()
{
	return 1000000;
}

void set_current_balance(int new_balance)
{
	return;
}
// shineer nemegdsen
void commun(int sock)
{
	char buf[BUF_SIZE];
	int balance = get_current_balance();

	read_until_delim(sock, buf, '_', BUF_SIZE);
	balance += atoi(buf);
	read_until_delim(sock, buf, '_', BUF_SIZE);
	balance -= atoi(buf);

	set_current_balance(balance);

	sprintf(buf, "%d_", balance);
	if (send(sock, buf, strlen(buf), 0) != strlen(buf))
		DieWithError("send() sent a message of unexpected bytes");
}