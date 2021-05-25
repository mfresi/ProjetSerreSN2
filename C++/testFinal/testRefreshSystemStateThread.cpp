//Module de test pour mettre à jour les valeurs des capteurs et actionneurs dans l'objet SystemData.
//Dev by Mattei Fresi

//Commande pour compiler -> g++ testRefreshSystemStateThread.cpp ../class/SystemData.cpp ../class/TCPServeur.cpp -o threadResfreshSystemState -lpthread 

#include "../class/SystemData.h"
#include "../class/TCPServeur.h"
#include <string>


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
        this_thread::sleep_for(chrono::seconds(10));
    } while (true);
}

using namespace std;

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
    tempMemory cache;

    tcpServeur.addListener(&myEventListener);

    if (!erreur)
    {
        thread updateCacheThread(updateCache, &cache);
        updateCacheThread.detach();

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
                        cout << "Un client s'est connecté" << endl;
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