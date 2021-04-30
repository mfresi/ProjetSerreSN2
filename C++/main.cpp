// ServerTCP avec multiClient qui gère la liaison entre le modbus et le site, écoute sur le port 9012.
// Dev by Mattei FRESI.
// command to compile file -> g++ main.cpp class/TCPServeur.cpp class/SystemData.cpp class/BDD.h -o output -L/usr/include/mariadb/mysql -lmariadbclient -lpthread && ./output

#include "class/TCPServeur.h"
#include "class/SystemData.h"
#include "class/BDD.h"

using namespace std;

class myServerEventListener : public TCPServerEventListener
{
public:
    virtual void onClientConnected(SOCKET csock, SOCKADDR_IN csinIp, SOCKADDR_IN csinPort)
    {
        cout << "Un client se connecte avec la socket " << csock << " avec l'ip " << inet_ntoa(csinIp.sin_addr) << " sur le port " << htons(csinPort.sin_port) << endl;
    };
};

void clientSession(TCPServeur tcpServeur, BDD Bdd)
{
    int resultReadBuffer;
    bool resultWriteToClient;
    bool resultRequest;
    bool resultCloseBdd;
    const char *req = "INSERT INTO `consommation`(`eau_pluie`, `eau_courante`, `electrique`) VALUES (666, 999, 444);";

    resultReadBuffer = tcpServeur.readBuffer();
    if (resultReadBuffer == true)
    {
        //TODO envoyer les valeurs des capteurs et actionneurs venant du cache.
        resultWriteToClient = tcpServeur.sendBufferToClient("18");

        if (resultWriteToClient == true)
        {
            cout << "Chaine envoyée avec succès" << endl;
            resultRequest = Bdd.query(req);
            if (resultRequest == true)
            {
                cout << "Insertion en BDD OK !" << endl;
            }
            else
            {
                cout << "Pas réussi à insérer en BDD" << endl;
            }
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
    bool resultInitializeBdd;
    bool resultConnectBdd;
    const char *host = "mysql-projet-serre-eau.alwaysdata.net";
    const char *login = "231030_mattei";
    const char *password = "37pgmh55";
    const char *bdd = "projet-serre-eau_bddeau";
    TCPServeur tcpServeur;
    BDD Bdd;
    myServerEventListener myEventListener;
    srand(time(NULL));
    //TODO Créer des valeurs aléatoires pour simuler les valeurs des capteurs et actionneurs venant du modbus.

    tcpServeur.addListener(&myEventListener);

    if (!erreur)
    {
        resultInitializeBdd = Bdd.initializeBdd();

        if (resultInitializeBdd == true)
        {
            cout << "Allouage de la mémoire pour Mysql OK" << endl;
            resultConnectBdd = Bdd.connectBdd(host, login, password, bdd);

            if (resultConnectBdd == true)
            {
                cout << "Connexion à la BDD OK !" << endl;
            }
            else
            {
                cout << "Pas réussi à connecter à la BDD" << endl;
            }
        }
        else
        {
            cout << "Pas réussi à allouer la mémoire pour Mysql" << endl;
        }
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
                        thread clientThread(clientSession, tcpServeur, Bdd);
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
