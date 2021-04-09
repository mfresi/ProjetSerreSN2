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
        // Méthode setsockopt qui permet la connexion multiClient.
        if (setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0)
        {
            perror("setsockopt");
            exit(EXIT_FAILURE);
        }
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

    if(this->csock != -1)
    {
        notifyClientConnected(csock, csin, csin);
        return true;
    }
    else
    {
        return false;
    }  
}
bool TCPServeur::readBuffer()
{
    char bufferClient[50] = {0};
    int resultReadBuffer;

    resultReadBuffer = recv(this->csock, &bufferClient, sizeof(bufferClient), 0);
    // Gestion d'erreur du nouveau socket
    if (resultReadBuffer == -1)
    {
        cout << "erreur lors de la reception du message client" << endl;
        return false;
    }
    else
    {
        // Le serveur affiche le message reçu
        cout << "Chaine reçu : " << bufferClient << endl;
        return true;
    }
}
bool TCPServeur::sendBufferToClient(char * bufferSendToClient)
{
    int resultWriteBuffer;

    resultWriteBuffer = send(csock, bufferSendToClient, strlen(bufferSendToClient), 0);

    if(resultWriteBuffer != SOCKET_ERROR)
    {
        cout << "Chaine envoyée : " << bufferSendToClient << endl;
        return true;
    }
        return false;
}
bool TCPServeur::closeSocket()
{
    int resultCloseSock;
    int resultCloseCsock;

    resultCloseSock = close(this->sock);
    resultCloseCsock = close(this->csock);

    if (resultCloseSock == 0 && resultCloseCsock == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void TCPServeur::addListener(TCPServerEventListener* l)
{
    listeners.push_back(l);
}

 void TCPServeur::notifyClientConnected(SOCKET csock, SOCKADDR_IN csinIp,SOCKADDR_IN csinPort)
{
    for(int i = 0; i < listeners.size(); i++)
    {
        listeners[i]->onClientConnected(csock, csinIp, csinPort);
    }
}