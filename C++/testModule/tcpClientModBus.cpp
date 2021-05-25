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
    int resultConnect;
    int error_message;
    int messageRecu;
    char bufferRecv[50];
    char bufferTemp[50];
    int tempValue;
    float trame = 0xE5;
    string Trame;
    // Création du socket.
    SOCKET sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN sin;
    // Parametrage la structure et verifier si c'est la bonne qui est envoyée.
    // inet_addr prend en paramètre l'IP de la machine où se trouve le server modbus.
    // htons prend en paramètre le port d'écoute du server modbus.
    sin.sin_addr.s_addr = inet_addr("192.168.65.120");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(502);

    resultConnect = connect(sock, (SOCKADDR *)&sin, sizeof(sin));

    if (resultConnect == 0)
    {
        cout << "connexion à la carte réussi" << endl;
    }
    else
    {
        cout << "pas réussi à se connecter à la carte" << endl;
    }
    // Déclaration du message à envoyé au serveur, dans notre cas "tcpClient"
    char buffer[12];
    buffer[0] = 0x00;
    buffer[1] = 0x01;
    buffer[2] = 0x00;
    buffer[3] = 0x00;
    buffer[4] = 0x00;
    buffer[5] = 0x06;
    buffer[6] = 0x01;
    buffer[7] = 0x04;
    buffer[8] = 0x00;
    buffer[9] = 0x63; // Adresse du capteur.
    buffer[10] = 0x00;
    buffer[11] = 0x02;

    // Envoie du buffer au serveur avec la méthode send().
    // Prend en paramètre le socket de type SOCKET, le buffer de type char, une taille de type int et un flag (0 par défaut). 
    error_message = send(sock, &buffer, 12, 0);
    // Gestion d'erreur de la méthode send().
    if (error_message == SOCKET_ERROR)
    {
        fprintf(stderr, "sendto message erreur : %s\n", strerror(errno));
    }
    else
    {
        cout << "Envoie à la carte réussi" << endl;
    }

    messageRecu = recv(sock, &bufferRecv, 13, 0);

    //cout << "Temperature : " + tempValue << endl;
    if (messageRecu != 0)
    {
        //printf("%2.2hhX \n", bufferRecv[12]);  
        //cout << "Temperature : " << dec << bufferRecv[12] << endl;
        snprintf(bufferTemp, 6, "0x%2.2hhX \n", bufferRecv[12]);

        float test = atof(bufferTemp);

        cout << dec << test/10 << " °C" << endl;
    }
    else
    {
        cout << "Pas réussi à lire zeubi" << endl;;
    }

    // Fermeture du socket avec la méthode close() qui prend en paramètre le socket de type SOCKET.
    close(sock);
}