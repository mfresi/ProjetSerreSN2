// ServerTCP avec multiClient qui gère la liaison entre le modbus et le site, écoute sur le port 9012.
// Dev by Mattei FRESI.
// command to compile file -> g++ ServerTcpMultithread.cpp -o output -L/usr/include/mariadb/mysql -lmariadbclient && ./output

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <mysql/mysql.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define TRUE 1
#define FALSE 0
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

int main()
{
#if defined(WIN32)
    WSADATA WSAData;
    int erreur = WSAStartup(MAKEWORD(2, 2), &WSAData);
#else
    int erreur = 0;
#endif

    // Initialisation des sockets et variables.

    SOCKET sock;
    SOCKADDR_IN sin;
    SOCKET csock;
    SOCKADDR_IN csin;
    char bufferInvalid[32] = "La chaine n'existe pas";
    char bufferDeco[512] = "deco";
    char bufferTemp[512] = "22.5";
    char bufferNiv1[512] = "bas";
    char bufferNiv2[512] = "haut";
    char bufferNiv3[512] = "haut";
    char bufferStopServer[512] = "Serveur arrêté";
    char bufferClient[50] = {0};
    socklen_t recsize = sizeof(csin);
    int sockBind_err;
    int sockSend_err;
    int sockRecv_err;
    int PORT = 9012;
    int opt = TRUE;
    bool etat = false;

    // Création de l'objet mysql.
    MYSQL mysql;
    char response;
    int result;
    const char * host = "mysql-projet-serre-eau.alwaysdata.net";
    const char * login = "231030_mattei";
    const char * password = "37pgmh55";
    const char * bdd = "projet-serre-eau_bddeau";
    const char * request = "INSERT INTO `consommation`(`eau_pluie`, `eau_courante`, `electrique`) VALUES (12, 45, 23);";

    if (!erreur)
    {
        // Création du socket
        sock = socket(AF_INET, SOCK_STREAM, 0);
        // gestion d'erreur du socket
        if (sock != INVALID_SOCKET)
        {
            // Méthode setsockopt qui permet la connexion multiClient.
            if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
            {
                perror("setsockopt");
                exit(EXIT_FAILURE);
            }
            // On montre à  l'utilisateur que le socket est créé
            printf("La socket %d est maintenant ouverte en mode TCPIP \n", sock);

            sin.sin_addr.s_addr = htonl(INADDR_ANY);
            sin.sin_family = AF_INET;
            sin.sin_port = htons(PORT);
            // On bind le serveur
            sockBind_err = bind(sock, (SOCKADDR *)&sin, sizeof(sin));
            // gestion d'erreur du bind
            if (sockBind_err != SOCKET_ERROR)
            {
                printf("Patientez pendant que le client se connecte sur le port %d... \n", PORT);
                // Connexion à la bade de donnée.
                mysql_init(&mysql);
                if (mysql_real_connect(&mysql, host, login, password, bdd, 0, NULL, 0))
                {
                    printf("Connexion à la BBD OK !\n");
                }
                else
                {
                    printf("Une erreur s'est produite lors de la connexion à la BDD!\n");
                }
                // Le serveur écoute se met en écoute et on accepte 6 connexions max.
                listen(sock, 6);
                // On reçoit le message envoyé par la source
                do
                {
                    // Le serveur accepte la communication avec la machine source
                    csock = accept(sock, (SOCKADDR *)&csin, &recsize);
                    printf("Un client se connecte avec la socket %d de %s sur le port %d \n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
                    sockRecv_err = recv(csock, &bufferClient, sizeof(bufferClient), 0);
                    // Gestion d'erreur du nouveau socket
                    if (sockRecv_err == -1)
                    {
                        printf("erreur lors de la reception du message client \n");
                    }
                    else
                    {
                        // Le serveur affiche le message reçu
                        printf("Chaine reçu  %s \n", bufferClient);
                    }
                    if (bufferClient[0] == '*')
                    {
                        sockSend_err = send(csock, bufferStopServer, strlen(bufferStopServer), 0);
                        etat = true;
                        if (sockSend_err != SOCKET_ERROR)
                        {
                            mysql_close(&mysql);
                            printf("Connexion à la base fermée\n");
                            printf("Chaine envoyée  %s \n", bufferStopServer);
                        }
                        else
                        {
                            printf("Erreur de transmission \n");

                            shutdown(csock, 2);
                        }
                    }
                    else if (bufferClient[0] == 't' && bufferClient[1] == 'e' && bufferClient[2] == 'm' && bufferClient[3] == 'p')
                    {
                        //Envoyer la trame au server modbus pour recuperer la temperature.
                        // Prend en paramètre un socket de type SOCKET, un buffer de type char, une taille de type int et un flag.
                        // Return SOCKET_ERROR si problème rencontré.
                        sockSend_err = send(csock, bufferTemp, strlen(bufferTemp), 0);
                        if (sockSend_err != SOCKET_ERROR)
                        {
                            result = mysql_real_query(&mysql, request, strlen(request));

                            if (result == 0)
                            {
                                printf("Insertion en base OK !\n");
                            }
                            else
                            {
                                printf("Insertion en base PAS OK !\n");
                            }

                            printf("Chaine envoyée  %s \n", bufferTemp);
                        }
                        else
                        {
                            printf("Erreur de transmissionn \n");

                            shutdown(csock, 2);
                        }
                    }
                    else if (bufferClient[0] == 'n' && bufferClient[1] == 'i' && bufferClient[2] == 'v' && bufferClient[3] == '1')
                    {
                        // Envoyer la trame au server modbus pour le niveau d'eau 1.
                        // Prend en paramètre un socket de type SOCKET, un buffer de type char, une taille de type int et un flag.
                        // Return SOCKET_ERROR si problème rencontré.
                        sockSend_err = send(csock, bufferNiv1, strlen(bufferNiv1), 0);
                        if (sockSend_err != SOCKET_ERROR)
                        {
                            printf("Chaine envoyée  %s \n", bufferNiv1);
                        }
                        else
                        {
                            printf("Erreur de transmission \n");

                            shutdown(csock, 2);
                        }
                    }
                    else if (bufferClient[0] == 'n' && bufferClient[1] == 'i' && bufferClient[2] == 'v' && bufferClient[3] == '2')
                    {
                        // Envoyer la trame au server modbus pour le niveau d'eau 2.
                        // Prend en paramètre un socket de type SOCKET, un buffer de type char, une taille de type int et un flag.
                        // Return SOCKET_ERROR si problème rencontré.
                        sockSend_err = send(csock, bufferNiv2, strlen(bufferNiv2), 0);
                        if (sockSend_err != SOCKET_ERROR)
                        {
                            printf("Chaine envoyée  %s \n", bufferNiv2);
                        }
                        else
                        {
                            printf("Erreur de transmission \n");

                            shutdown(csock, 2);
                        }
                    }
                    else if (bufferClient[0] == 'n' && bufferClient[1] == 'i' && bufferClient[2] == 'v' && bufferClient[3] == '3')
                    {
                        // Envoyer la trame au server modbus pour le niveau d'eau 3.
                        // Prend en paramètre un socket de type SOCKET, un buffer de type char, une taille de type int et un flag.
                        // Return SOCKET_ERROR si problème rencontré.
                        sockSend_err = send(csock, bufferNiv3, strlen(bufferNiv3), 0);
                        if (sockSend_err != SOCKET_ERROR)
                        {
                            printf("Chaine envoyée  %s \n", bufferNiv3);
                        }
                        else
                        {
                            printf("Erreur de transmission \n");

                            shutdown(csock, 2);
                        }
                    }
                    else
                    {
                        // Prend en paramètre un socket de type SOCKET, un buffer de type char, une taille de type int et un flag.
                        // Return SOCKET_ERROR si problème rencontré.
                        sockSend_err = send(csock, bufferInvalid, strlen(bufferInvalid), 0);
                        if (sockSend_err != SOCKET_ERROR)
                        {
                            printf("Chaine envoyée  %s \n", bufferInvalid);
                        }
                        else
                        {
                            printf("Erreur de transmission \n");

                            shutdown(csock, 2);
                        }
                    }
                } while (etat != true);
            }
            else
            {
                printf("Pas reussi à bind le server \n");
            }
            // Fermeture des sockets.
            printf("Fermeture de la socket... \n");
            close(sock);
            close(csock);
            printf("Fermeture du serveur terminee \n");
        }
        else
        {
            printf("Pas reussi à creer la socket \n");
        }

#if defined(WIN32)
        WSACleanup();
#endif
    }
}
