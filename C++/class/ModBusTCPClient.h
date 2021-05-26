// Déclaration de la classe ModBusTCPClient.
// Permet de communiquer avec la carte E/S par protocole modbus pour récupérer les valeurs des capteurs et piloter les actionneurs avec les classes Capteurs et Actionneurs.
// Dev by Frezale.
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

    bool createSocket();
    bool connectSocket(const char * address, int port);
    bool sendBuffer(char octet1, char octet2, char octet3, char octet4, char octet5, char octet6, char octet7, char octet8, char octet9, char octet10, char octet11, char octet12);
    float recvTemperature();
    int recvWaterLevel();
    float recvWaterConso();
    bool closeSocket();
};