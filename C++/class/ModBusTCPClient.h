#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <iostream>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
using namespace std;

class ModBusTCPClient {

private:

    SOCKET sock;
    SOCKADDR_IN sin;

public:

    createSocket();
    connectSocket(char address, int port);
    sendBuffer();
    recvBuffer();
    closeSocket();
}