#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <stdint.h>

typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef int SOCKET;
#define INVALID_SOCKET -1

int main(int argc, char ** argv)
{
	SOCKADDR_IN sin;
	char buffer[255];
	int transactionId = 0;

	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock != INVALID_SOCKET)
    {   int yes = 1;
	setsockopt(sock, IPPROTO_TCP, TCP_CORK, (void*)&yes,sizeof(int));
	yes = 0;
        int result = setsockopt(sock,IPPROTO_TCP,TCP_NODELAY,(void*)&yes,sizeof(int));
    }

    sin.sin_addr.s_addr = inet_addr("192.168.65.120");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(502);
	connect(sock, (SOCKADDR *)&sin, sizeof(sin));

	bool state = true;

	while (1)
	{
		buffer[0] = (transactionId & 0xFF00) >> 8;
		buffer[1] = transactionId & 0x00FF;
		buffer[2] = 0x00;
		buffer[3] = 0x00;
		buffer[4] = 0x00;
		buffer[5] = 0x06;
		buffer[6] = 0xff;
		buffer[7] = 0x05;
		buffer[8] = 0x00;
		buffer[9] = 0xc7;
		buffer[10] = state ? 0xFF : 0x00;
		buffer[11] = 0x00;

		transactionId++;

		printf("Send 1\n");
		send(sock, buffer, 12, MSG_EOR);
		printf("Send 1 end\n");
		int flag = 0;
		//setsockopt(sock, IPPROTO_TCP, TCP_CORK, (void*)&flag, sizeof(flag));
		flag = ~flag;
		//setsockopt(sock, IPPROTO_TCP, TCP_CORK, (void*)&flag, sizeof(flag));

		buffer[0] = (transactionId & 0xFF00) >> 8;
		buffer[1] = transactionId & 0x00FF;
		buffer[9] = 0xc8;
		buffer[10] = state ? 0xFF : 0x00;

		transactionId++; 

		printf("Send 2\n");
		send(sock, buffer, 12, MSG_EOR);
		printf("Send 2 end\n");
		flag = 0;
                //setsockopt(sock, IPPROTO_TCP, TCP_CORK, (void*)&flag, sizeof(flag));
                flag = ~flag;
                //setsockopt(sock, IPPROTO_TCP, TCP_CORK, (void*)&flag, sizeof(flag));

		sleep(1);

		state = !state;
	}

	return 0;
}
