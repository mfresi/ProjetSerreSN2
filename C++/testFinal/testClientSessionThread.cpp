// Programme de test pour le thread clientSession qui permet une connexion au serveur TCP avec plusieurs client en multiThread.
// Dev by Mattei Fresi

// command to compile file -> g++ testClientSessionThread.cpp ../class/TCPServeur.cpp -o threadClient -lpthread 

#include "../class/TCPServeur.h"

using namespace std;

class myServerEventListener : public TCPServerEventListener
{
public:
    virtual void onClientConnected(SOCKET csock, SOCKADDR_IN csinIp, SOCKADDR_IN csinPort)
    {
        cout << "Un client se connecte avec la socket " << csock << " avec l'ip " << inet_ntoa(csinIp.sin_addr) << " sur le port " << htons(csinPort.sin_port) << endl;
    };
};

void clientSession(TCPServeur tcpServeur)
{
    int resultReadBuffer;
    bool resultWriteToClient;

    resultReadBuffer = tcpServeur.readBuffer();
    if (resultReadBuffer != -1)
    {
        if (resultReadBuffer == 4)
        {
            resultWriteToClient = tcpServeur.sendBufferToClient("Temperature : 18 °C");
        }
        else if (resultReadBuffer == 1)
        {
            resultWriteToClient = tcpServeur.sendBufferToClient("Niveau d'eau 1 : bas");
        }
        else if (resultReadBuffer == 2)
        {
            resultWriteToClient = tcpServeur.sendBufferToClient("Niveau d'eau 2 : haut");
        }
        else if (resultReadBuffer == 3)
        {
            resultWriteToClient = tcpServeur.sendBufferToClient("Niveau d'eau 3 : bas");
        }
        else if (resultReadBuffer == 5)
        {
            resultWriteToClient = tcpServeur.sendBufferToClient("Pompe : en fonction");
        }
        else if (resultReadBuffer == 6)
        {
            resultWriteToClient = tcpServeur.sendBufferToClient("reseau eau : pluie");
        }
        else if (resultReadBuffer == 0)
        {
            resultWriteToClient = tcpServeur.sendBufferToClient("Ce capteur n'existe pas");
        }

        if (resultWriteToClient == true)
        {
            cout << "Chaine envoyée avec succès" << endl;
        }
        else
        {
            cout << "Pas réussi à envoyer la chaine" << endl;
        }
    }
    else
    {
        cout << "Pas réussi à lire la chaine" << endl;
    }
}

int main()
{
#if defined(WIN32)
    WSADATA WSAData;
    int erreur = WSAStartup(MAKEWORD(2, 2), &WSAData);
#else
    int erreur = 0;
#endif

    bool resultCreateSocket;
    bool resultBindServer;
    bool resultAcceptCom;
    bool etat = false;
    TCPServeur tcpServeur;
    myServerEventListener myEventListener;

    tcpServeur.addListener(&myEventListener);

    if (!erreur)
    {
        resultCreateSocket = tcpServeur.createSocket();

        if (resultCreateSocket == true)
        {
            resultBindServer = tcpServeur.connectServer(9012);

            if (resultBindServer == true)
            {
                do
                {
                    resultAcceptCom = tcpServeur.acceptCom();

                    if (resultAcceptCom == true)
                    {
                        thread clientThread(clientSession, tcpServeur);
                        clientThread.detach();
                    }
                    else
                    {
                        cout << "Problème lorque le client essaie de se connecter" << endl;
                    }
                } while (etat != true);
            }
            else
            {
                cout << "Pas réussi à bind le serveur" << endl;
            }
        }
        else
        {
            cout << "Pas réussi à créer le socket" << endl;
        }
#if defined(WIN32)
        WSACleanup();
#endif
    }
}