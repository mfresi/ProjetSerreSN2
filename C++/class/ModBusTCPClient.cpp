// Implémentation des méthodes de la classe ModBusTCPClient.
// Dev by Frezale.
#include "ModBusTCPClient.h"
// Méthode createSocket de type bool qui permet de créer un socket.
// Return true en cas de succès et false en cas d'échec.
bool ModBusTCPClient::createSocket()
{
    transactionId = 0;
    this->sock = socket(AF_INET, SOCK_STREAM, 0);

    if (this->sock != INVALID_SOCKET)
    {   
    {   int yes = 1;
	setsockopt(sock, IPPROTO_TCP, TCP_CORK, (void*)&yes,sizeof(int));
	yes = 0;
    int result = setsockopt(sock,IPPROTO_TCP,TCP_NODELAY,(void*)&yes,sizeof(int));
    }
        return true;
    }
    else
    {
        return false;
    }
}
// Méthode connectSocket de type bool qui prend en paramètre une adresse de type const char * et un port de type int.
// Return true en cas de succès et false en cas d'échec.
bool ModBusTCPClient::connectSocket(const char *address, int port)
{
    // Mettre 192.168.65.120 pour l'adresse et 502 pour le port.
    sin.sin_addr.s_addr = inet_addr(address);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);

    int resultConnect = connect(this->sock, (SOCKADDR *)&sin, sizeof(sin));

    if (resultConnect == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// Méthode sendBuffer de type bool qui prend en paramètre les 12 octets de la trame d'envoie.
// Return true en cas de succès et false en cas d'échec.
bool ModBusTCPClient::sendBuffer(char octet1, char octet2, char octet3, char octet4, char octet5, char octet6, char octet7, char octet8, char octet9, char octet10, char octet11, char octet12)
{
    char buffer[12];
    buffer[0] = (transactionId & 0xFF00) >> 8;
    buffer[1] = (transactionId & 0x00FF);
    transactionId++;
    buffer[2] = 0x00;
    buffer[3] = 0x00;
    buffer[4] = 0x00;
    buffer[5] = 0x06;
    buffer[6] = 0x00;
    buffer[7] = octet8;
    buffer[8] = octet9;
    buffer[9] = octet10; // Adresse du capteur.
    buffer[10] = octet11;
    buffer[11] = octet12;

    int error_message = send(this->sock, buffer, 12, MSG_EOR);
    // Gestion d'erreur de la méthode send().
    if (error_message == SOCKET_ERROR)
    {
        return false;
    }
    else
    {
        return true;
    }
}
// Permet le traitement de la trame de réception du capteur de température.
// Return la valeur de la température en cas de succès et false en cas d'echec.
float ModBusTCPClient::recvTemperature()
{
    char bufferRecv[50];
    char bufferTempOctet11[50];
    char bufferTempOctet12[50];
    char bufferT[50];

    int messageRecu = recv(sock, bufferRecv, 13, 0);

    if (messageRecu != 0)
    {
        snprintf(bufferTempOctet11, 6, "0x%2.2hhX \n", bufferRecv[11]);
        snprintf(bufferTempOctet12, 6, "0x%2.2hhX \n", bufferRecv[12]);
        float temp2 = atof(bufferTempOctet11);
        float temp = atof(bufferTempOctet12);

        if (temp <= 255 && temp2 == 0)
        {
            return temp / 10;
        }
        else
        {
            return (temp2 * (16 * 16) + temp) / 10;
        }
    }
    else
    {
        return false;
    }
}
// Permet le traitment de la trame pour les capteurs de niveau d'eau.
// Return l'etat des niveau d'eau en cas de succès et -1 en cas d'echec.
int ModBusTCPClient::recvWaterLevel()
{
    char bufferRecv[50];
    char bufferTemp[50];

    int messageRecu = recv(sock, bufferRecv, 11, 0);

    if (messageRecu != 0)
    {
        snprintf(bufferTemp, 6, "0x%2.2hhX \n", bufferRecv[9]);
        int waterLevel = atof(bufferTemp);
        return waterLevel;
    }
    else
    {
        return -1;
    }
}
// Permet de traiter la trame de reception du capteur de consommation d'eau.
// Return la consommation d'eau en Litre en cas de succès et false en cas d'echec.
float ModBusTCPClient::recvWaterConso()
{

    char bufferRecv[50];
    char bufferTempOctet9[50];
    char bufferTempOctet10[50];
    char bufferT[50];

    int messageRecu = recv(sock, bufferRecv, 11, 0);

    if (messageRecu != 0)
    {
        snprintf(bufferTempOctet9, 6, "0x%2.2hhX \n", bufferRecv[9]);
        snprintf(bufferTempOctet10, 6, "0x%2.2hhX \n", bufferRecv[10]);
        float Waterconso2 = atof(bufferTempOctet9);
        float Waterconso1 = atof(bufferTempOctet10);

        if (Waterconso1 <= 255 && Waterconso2 == 0)
        {
            return Waterconso1 / 10;
        }
        else
        {
            return (Waterconso2 * (16 * 16) + Waterconso1) / 10;
        }
    }
    else
    {
        return false;
    }
}
// Permet de mettre fin à la connexion avec la carte E/S.
// Return true en cas de succès et false en cas d'echec.
bool ModBusTCPClient::closeSocket()
{
    int resultCloseSocket;

    resultCloseSocket = close(this->sock);

    if (resultCloseSocket == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
