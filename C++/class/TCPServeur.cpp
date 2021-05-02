#include "TCPServeur.h"

using namespace std;

TCPServeur::TCPServeur()
{
}
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
bool TCPServeur::acceptCom()
{
    // Le serveur accepte la communication avec la machine source
    this->csock = accept(this->sock, (SOCKADDR *)&this->csin, &this->recsize);

    if (this->csock != -1)
    {
        notifyClientConnected(csock, csin, csin);
        return true;
    }
    else
    {
        return false;
    }
}
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
            cout << "le client demande l'etat du réseau d'eau" << endl;
            return 6;
        }
        else
        {
            return 0;
        }
    }
}
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

void TCPServeur::addListener(TCPServerEventListener *l)
{
    listeners.push_back(l);
}

void TCPServeur::notifyClientConnected(SOCKET csock, SOCKADDR_IN csinIp, SOCKADDR_IN csinPort)
{
    for (int i = 0; i < listeners.size(); i++)
    {
        listeners[i]->onClientConnected(csock, csinIp, csinPort);
    }
}