// Module de test pour communiquer avec le server modbus simulator.
// Dev by Mattei FRESI

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

// Mise en place d'un client TCP qui envoie sur le port 9012
using namespace std;

int main()
{
    // Création du socket.
    SOCKET sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN sin;
    // Parametrage la structure et verifier si c'est la bonne qui est envoyée.
    // inet_addr prend en paramètre l'IP de la machine où se trouve le server modbus.
    // htons prend en paramètre le port d'écoute du server modbus.
    sin.sin_addr.s_addr = inet_addr("192.168.1.90");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(502);

    connect(sock, (SOCKADDR *)&sin, sizeof(sin));
    // Déclaration du message à envoyé au serveur, dans notre cas "tcpClient"
    // trame test -> 00 00 00 00 00 06 FF 06 00 10 00 FF
    char buffer[10];
    buffer[0] = 0x00;
    buffer[1] = 0x00;
    buffer[2] = 0x00;
    buffer[3] = 0x00;
    buffer[4] = 0x00;
    buffer[5] = 0x06;
    buffer[6] = 0xFF;
    buffer[7] = 0x06;
    buffer[8] = 0x00;
    buffer[9] = 0x10;
    buffer[10] = 0x00;
    buffer[11] = 0xFF;

    int error_message;

    // Envoie du buffer au serveur avec la méthode send().
    // Prend en paramètre le socket de type SOCKET, le buffer de type char, une taille de type int et un flag (0 par défaut). 
    error_message = send(sock, buffer, 12, 0);
    // Gestion d'erreur de la méthode send().
    if (error_message == 0)
    {
        fprintf(stderr, "sendto message erreur : %s\n", strerror(errno));
    }
    // Fermeture du socket avec la méthode close() qui prend en paramètre le socket de type SOCKET.
    close(sock);
}