// Implémenation des méthodes de la classe TCPServeur.
#include "TCPServeur.h"

using namespace std;

TCPServeur::TCPServeur()
{
}
// Permet de créer le socket pour la connexion TCP.
// Return true en cas de succès et false en cas d'echec.
bool TCPServeur::createSocket()
{
    int opt = TRUE;
    // Création du socket
    this->sock = socket(AF_INET, SOCK_STREAM, 0);

    if (this->sock != INVALID_SOCKET)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// Permet de bind le serveur TCP sur un port.
// Return true en cas de succès et false en cas d'echec.
bool TCPServeur::connectServer(int port)
{
    int resultBindServer;

    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);

    resultBindServer = bind(this->sock, (SOCKADDR *)&sin, sizeof(sin));

    if (resultBindServer != SOCKET_ERROR)
    {
        cout << "Patientez pendant que le client se connecte sur le port " << port << "..." << endl;
        listen(this->sock, 6);
        return true;
    }
    else
    {
        return false;
    }
}
// Le serveur attend une connexion client.
// Return true en cas de succès et false en cas d'echec.
bool TCPServeur::acceptCom()
{
    // Le serveur accepte la communication avec la machine source
    this->csock = accept(this->sock, (SOCKADDR *)&this->csin, &this->recsize);

    if (this->csock != -1)
    {
        // Mise en place de l'event pour notifier le serveur d'une connexion client immédiate.
        notifyClientConnected(csock, csin, csin);
        return true;
    }
    else
    {
        return false;
    }
}
// Permet de traiter le protocole instauré par les étudiants 1 et 2 entre le serveur TCP et l'interface Web.
// Return un int en cas de succès et -1 en cas d'echec.
int TCPServeur::readBuffer()
{
    char bufferClient[50] = {0};
    int resultReadBuffer;

    resultReadBuffer = recv(this->csock, &bufferClient, sizeof(bufferClient), 0);
    // Gestion d'erreur du nouveau socket
    if (resultReadBuffer == -1)
    {
        cout << "erreur lors de la reception du message client" << endl;
        return -1;
    }
    else
    {
        // Le serveur affiche le message reçu
        cout << "Chaine reçu : " << bufferClient << endl;
        if (bufferClient[0] == 't' && bufferClient[1] == 'e' && bufferClient[2] == 'm' && bufferClient[3] == 'p')
        {
            cout << "le client demande la temperature" << endl;
            return 4;
        }
        else if (bufferClient[0] == 'n' && bufferClient[1] == 'i' && bufferClient[2] == 'v' && bufferClient[3] == '1')
        {
            cout << "le client demande le niveau d'eau 1" << endl;
            return 1;
        }
        else if (bufferClient[0] == 'n' && bufferClient[1] == 'i' && bufferClient[2] == 'v' && bufferClient[3] == '2')
        {
            cout << "le client demande le niveau d'eau 2" << endl;
            return 2;
        }
        else if (bufferClient[0] == 'n' && bufferClient[1] == 'i' && bufferClient[2] == 'v' && bufferClient[3] == '3')
        {
            cout << "le client demande le niveau d'eau 3" << endl;
            return 3;
        }
        else if (bufferClient[0] == 'p' && bufferClient[1] == 'o' && bufferClient[2] == 'm' && bufferClient[3] == 'p' && bufferClient[4] == 'e')
        {
            cout << "le client demande l'etat de la pompe" << endl;
            return 5;
        }
        else if (bufferClient[0] == 'e' && bufferClient[1] == 'a' && bufferClient[2] == 'u')
        {
            cout << "le client demande l'état du réseau d'eau" << endl;
            return 6;
        }
         else if (bufferClient[0] == 'w' && bufferClient[1] == 'a' && bufferClient[2] == 't' && bufferClient[3] == 'e' && bufferClient[4] == 'r')
        {
            cout << "le client demande la consommation d'eau" << endl;
            return 7;
        }
         else if (bufferClient[0] == 'e' && bufferClient[1] == 'l' && bufferClient[2] == 'e' && bufferClient[3] == 'c')
        {
            cout << "le client demande la consommation electrique" << endl;
            return 8;
        }
        else
        {
            return 0;
        }
    }
}
// Permet d'envoyer des informations à l'interface Web.
// Return true en cas de succès et false en cas d'echec.
bool TCPServeur::sendBufferToClient(const char *bufferSendToClient)
{
    int resultWriteBuffer;

    resultWriteBuffer = send(csock, bufferSendToClient, strlen(bufferSendToClient), 0);

    if (resultWriteBuffer != SOCKET_ERROR)
    {
        cout << "Chaine envoyée : " << bufferSendToClient << endl;
        return true;
    }
    return false;
}
// Permet de fermer la connexion client.
// Return true en cas de succès et false en cas d'echec.
bool TCPServeur::closeSocketClient()
{
    int resultCloseCSock;

    resultCloseCSock = close(this->csock);

    if (resultCloseCSock == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// Permet de fermer la connexion sur serveur TCP.
// Return true en cas de succès et false en cas d'echec.
bool TCPServeur::closeListenSocket()
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
// Permet d'ajouter des events.
void TCPServeur::addListener(TCPServerEventListener *l)
{
    listeners.push_back(l);
}
// Permet de notifier le serveur quand un client se connecte au serveur TCP.
void TCPServeur::notifyClientConnected(SOCKET csock, SOCKADDR_IN csinIp, SOCKADDR_IN csinPort)
{
    for (int i = 0; i < listeners.size(); i++)
    {
        listeners[i]->onClientConnected(csock, csinIp, csinPort);
    }
}
