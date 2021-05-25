// ServerTCP avec multiClient qui gère la liaison entre le modbus et le site, écoute sur le port 9012.
// Dev by Mattei FRESI.
// command to compile file -> g++ main.cpp class/TCPServeur.cpp class/SystemData.cpp class/BDD.cpp -o output -L/usr/include/mariadb/mysql -lmariadbclient -lpthread && ./output
// compile without mysql lib -> g++ main.cpp class/TCPServeur.cpp class/SystemData.cpp -o output -lpthread && ./output

#include "class/TCPServeur.h"
#include "class/SystemData.h"
//#include "class/BDD.h"
#include <string>

using namespace std;

class myServerEventListener : public TCPServerEventListener
{
public:
    virtual void onClientConnected(SOCKET csock, SOCKADDR_IN csinIp, SOCKADDR_IN csinPort)
    {
        cout << "Un client se connecte avec la socket " << csock << " avec l'ip " << inet_ntoa(csinIp.sin_addr) << " sur le port " << htons(csinPort.sin_port) << endl;
    };
};

void getRandomValues(tempMemory *cache)
{
    // Temperature comprise entre 0 et 10.
    float temperature = rand() % 30;
    // Niveau d'eau compris entre 0 et 1.
    int niveauEau1 = rand() % 2;
    int niveauEau2 = rand() % 2;
    int niveauEau3 = rand() % 2;
    // Consommation électrique comprise entre 0 et 30.
    int electricalConsommation = rand() % 30;
    // Pompe : 0 -> non active || 1 -> en cours d'activité.
    bool pompe = rand() % 2;
    // Réseau d'eau : 0 -> eau courante || 1 -> eau de pluie.
    bool eau = rand() % 2;
    // Met à jour la valeur du cache SystemData avec les valeurs aléatoires pour le module de test.
    cache->saveValueInCache(temperature, niveauEau1, niveauEau2, niveauEau3, electricalConsommation, pompe, eau);
}

void clientSession(TCPServeur tcpServeur, tempMemory cache)
{
    int resultReadBuffer;
    bool resultWriteToClient;
    bool resultRequest;
    bool resultCloseBdd;
    string temperature;
    string waterLevel1;
    string waterLevel2;
    string waterLevel3;
    string pompe;
    string eau;
    temperature = to_string((int)cache.systemData.temperatureValue);
    waterLevel1 = to_string(cache.systemData.waterLevelValue1);
    waterLevel2 = to_string(cache.systemData.waterLevelValue2);
    waterLevel3 = to_string(cache.systemData.waterLevelValue3);
    pompe = to_string(cache.systemData.pompe);
    eau = to_string(cache.systemData.eau);
    const char *req = "INSERT INTO `consommation`(`eau_pluie`, `eau_courante`, `electrique`) VALUES (" + cache.systemData.temperatureValue + ", " + cache.systemData.waterLevel1 + ", " + cache.systemData.waterLevel3 + ");";

    resultReadBuffer = tcpServeur.readBuffer();
    if (resultReadBuffer != -1)
    {
        if (resultReadBuffer == 4)
        {
            resultWriteToClient = tcpServeur.sendBufferToClient(temperature.c_str());
        }
        else if (resultReadBuffer == 1)
        {
            resultWriteToClient = tcpServeur.sendBufferToClient(waterLevel1.c_str());
        }
        else if (resultReadBuffer == 2)
        {
            resultWriteToClient = tcpServeur.sendBufferToClient(waterLevel2.c_str());
        }
        else if (resultReadBuffer == 3)
        {
            resultWriteToClient = tcpServeur.sendBufferToClient(waterLevel3.c_str());
        }
        else if (resultReadBuffer == 5)
        {
            resultWriteToClient = tcpServeur.sendBufferToClient(pompe.c_str());
        }
        else if (resultReadBuffer == 6)
        {
            resultWriteToClient = tcpServeur.sendBufferToClient(eau.c_str());
        }
        else if (resultReadBuffer == 0)
        {
            resultWriteToClient = tcpServeur.sendBufferToClient("Ce capteur n'existe pas");
        }

        tcpServeur.closeSocketClient();

        /* if (resultWriteToClient == true)
        {
            cout << "Chaine envoyée avec succès" << endl;
            /*resultRequest = Bdd.query(req);
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
        } */
    }
    else
    {
        cout << "Pas réussi à lire la chaine" << endl;
    } 
}

void updateCache(tempMemory *cache)
{
    srand(time(NULL));
    do
    {
        cout << "Mise à jour du cache ..." << endl;
        getRandomValues(cache);
        cout << "Temperature : " << cache->systemData.temperatureValue << endl;
        cout << "niveau d'eau 1 : " << cache->systemData.waterLevelValue1 << endl;
        cout << "niveau d'eau 2 : " << cache->systemData.waterLevelValue2 << endl;
        cout << "niveau d'eau 3 : " << cache->systemData.waterLevelValue3 << endl;
        cout << "consommation electrique : " << cache->systemData.electricalConsommationValue << endl;
        cout << "Etat de la pompe : " << cache->systemData.pompe << endl;
        cout << "Reseau d'eau : " << cache->systemData.eau << endl;
        // Mettre une attente de 1 minute.
        this_thread::sleep_for(chrono::seconds(60));
    } while (true);
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
    //BDD Bdd;
    myServerEventListener myEventListener;
    tempMemory cache;

    tcpServeur.addListener(&myEventListener);

    if (!erreur)
    {
        thread updateCacheThread(updateCache, &cache);
        updateCacheThread.detach();
        //resultInitializeBdd = Bdd.initializeBdd();

       /* if (resultInitializeBdd == true)
        {
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
        } */
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
                        thread clientThread(clientSession, tcpServeur, cache);
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
