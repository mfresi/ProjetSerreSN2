// ServerTCP avec multiClient qui gère la liaison entre le modbus et le site, écoute sur le port 9012.
// Dev by Mattei FRESI.
// command to compile file -> g++ main.cpp class/TCPServeur.cpp -o output -L/usr/include/mariadb/mysql -lmariadbclient && ./output

#include "class/TCPServeur.h"

struct systemData
{
    float temperatureValue;
    bool waterLevelValue;
    int electricalConsommationValue;

} systemData;

using namespace std;

class myServerEventListener : public TCPServerEventListener
{
public:
    virtual void onClientConnected(SOCKET csock, SOCKADDR_IN csinIp, SOCKADDR_IN csinPort)
    {
        cout << "Un client se connecte avec la socket " << csock << " avec l'ip " << inet_ntoa(csinIp.sin_addr) << " sur le port " << htons(csinPort.sin_port) << endl;
    };
};

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
    int resultReadBuffer;
    bool resultAcceptCom;
    bool resultWriteToClient;
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
                        resultReadBuffer = tcpServeur.readBuffer();
                        if (resultReadBuffer == true)
                        {
                            resultWriteToClient = tcpServeur.sendBufferToClient("18");

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
                    else
                    {
                        cout << "Problème lorque le client essaie de se connecter" << endl;
                    }
                } while(etat != true);
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
