// ServerTCP avec multiClient qui gère la liaison entre le modbus et le site, écoute sur le port 9012.
// Dev by Mattei FRESI.
// command to compile file -> g++ main.cpp class/TCPServeur.cpp class/tempMemory.cpp class/BDD.cpp class/Capteurs.cpp class/ModBusTCPClient.cpp class/Actionneurs.cpp -o output $(mysql_config --cflags) $(mysql_config --libs) -lpthread && ./output
// compile without mysql lib -> g++ main.cpp class/TCPServeur.cpp class/tempMemory.cpp class/Capteurs.cpp class/ModBusTCPClient.cpp -o output -lpthread && ./output

#include "class/TCPServeur.h"
#include "class/tempMemory.h"
#include "class/Capteurs.h"
#include "class/BDD.h"
#include "class/Actionneurs.h"
#include <string>
#include <mutex>
#include <ctime>

using namespace std;

class myServerEventListener : public TCPServerEventListener
{
public:
    virtual void onClientConnected(SOCKET csock, SOCKADDR_IN csinIp, SOCKADDR_IN csinPort)
    {
        cout << "Un client se connecte avec la socket " << csock << " avec l'ip " << inet_ntoa(csinIp.sin_addr) << " sur le port " << htons(csinPort.sin_port) << endl;
    };
};

std::mutex synchro;

void getSystemData(tempMemory *cache, Capteurs capteurs, Actionneurs actionneurs, BDD bdd)
{  
    // date / heure actuelle basée sur le système actuel
    time_t actuel = time(0);
    tm *ltm = localtime(&actuel);
    // afficher divers member de la structure tm.
    int annee = 1900 + ltm->tm_year;
    int mois = 1 + ltm->tm_mon;
    int jour = ltm->tm_mday;
    int heures = ltm->tm_hour;
    int minutes = ltm->tm_min;
    float temperature = capteurs.getTemperature();
    int etatWaterLevel = capteurs.getNiveauEau();
    int waterConso = capteurs.getWaterconsommation();
    bool waterLevel1;
    bool waterLevel2;
    bool pompe;
    bool eau;
    int ElectricalConso = rand() % 30;
    bool waterLevel3 = 0;
    int consoEauCourante;
    int consoEauPluie;
    const char *host = "192.168.65.54";
    const char *login = "root";
    const char *password = "root";
    const char *Bdd = "Serre";
    char DATE[10];
    char archiveDate[10];
    snprintf(DATE, 11, "%d-0%d-%d\n", annee, mois, jour);
    string waterconso;
    string electricalConso;
    string date = DATE;
    string heure;
    electricalConso = to_string(ElectricalConso);
    waterconso = to_string(waterConso);
    heure = to_string(heures);
    string request = "INSERT INTO `consommation`(`eau_pluie`, `eau_courante`, `electrique`, `date`, `heure`) VALUES (" + waterconso + " , " + waterconso + ", " + electricalConso + ", '" + date + "', '" + heure + "');";
    string requestToArchive = "INSERT INTO `archives`(`eau_pluie`, `eau_courante`, `electrique`, `date`, `heure`) SELECT `eau_pluie`, `eau_courante`, `electrique`, `date`, `heure` FROM `consommation`;";
    string purgeRequest = "TRUNCATE TABLE `consommation`;";
    bool resultInitializeBdd;
    bool resultConnectBdd;
    bool resultQuery;
    bool resultQueryArchivage;
    bool resultPurge;

    resultInitializeBdd = bdd.initializeBdd();

    if (resultInitializeBdd == true)
    {
        resultConnectBdd = bdd.connectBdd(host, login, password, Bdd);

        if (resultConnectBdd == true)
        {
            cout << "Connexion à la BDD OK !" << endl;
            resultQuery = bdd.query(request.c_str());

            if (resultQuery == true)
            {
                cout << "Insertion en base OK" << endl;
            }
            else
            {
                cout << "Pas réussi à insert en base" << endl;
            }

            if (heures == 00)
            {
                resultQueryArchivage = bdd.query(requestToArchive.c_str());

                if (resultQueryArchivage == true)
                {
                    cout << "Archivage OK" << endl;
                    resultPurge = bdd.query(purgeRequest.c_str());
                    bdd.closeBdd();

                    if (resultPurge == true)
                    {
                        cout << "Table purge" << endl;
                    }
                    else
                    {
                        cout << "Pas réussi à purger" << endl;
                    }
                }
                else
                {
                    cout << "Pas réussi à archiver" << endl;
                }
            }
            else
            {
                cout << "Pas la bonne heure pour archiver" << endl;
            }
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

    if (etatWaterLevel == 0)
    {
        waterLevel1 = 0;
        waterLevel2 = 0;
        cout << "On utilise l'eau courante" << endl;
        if (pompe != 1)
        {
            actionneurs.SetReseauEauCourante();
            pompe = 0;
        }
        eau = 0;
    }
    else if (temperature < 2)
    {
        cout << "On utilise l'eau courante" << endl;
        actionneurs.SetReseauEauCourante();
        eau = 0;
        pompe = 0;
    }

    else if (etatWaterLevel == 1)
    {
        waterLevel1 = 1;
        waterLevel2 = 0;

        cout << "On active la pompe" << endl;
        actionneurs.SetPumpON();
        pompe = 1;
    }

    else if (etatWaterLevel == 2)
    {
        waterLevel1 = 0;
        waterLevel2 = 1;
        actionneurs.SetPumpOFF();
        //usleep(1500);
        pompe = 0;
        cout << "on utilise l'eau de pluie" << endl;
        actionneurs.SetReseauEauPluie();
        eau = 1;
    }
    else if (etatWaterLevel == 3)
    {
        waterLevel1 = 1;
        waterLevel2 = 1;
        actionneurs.SetPumpOFF();
        //usleep(1500);
        cout << "on utilise l'eau de pluie" << endl;
        actionneurs.SetReseauEauPluie();
        pompe = 0;
        eau = 1;
    }

    if (eau == 1)
    {   
        consoEauPluie = waterConso;
    }
    else if (eau == 0)
    {
        consoEauCourante = waterConso;
    }
    // Met à jour la valeur du cache SystemData avec les valeurs aléatoires pour le module de test.
    cache->refreshSystemState(temperature, waterLevel1, waterLevel2, waterLevel3, waterConso, ElectricalConso, pompe, eau, consoEauCourante, consoEauPluie);
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
    string waterConso;
    string electricalConso;

    synchro.lock();
    temperature = to_string((float)cache.systemData.temperatureValue);
    waterLevel1 = to_string(cache.systemData.waterLevelValue1);
    waterLevel2 = to_string(cache.systemData.waterLevelValue2);
    waterLevel3 = to_string(cache.systemData.waterLevelValue3);
    waterConso = to_string(cache.systemData.waterConsommationValue);
    electricalConso = to_string(cache.systemData.electricalConsommationValue);
    pompe = to_string(cache.systemData.pompe);
    eau = to_string(cache.systemData.eau);
    synchro.unlock();
    //const char *req = "INSERT INTO `consommation`(`eau_pluie`, `eau_courante`, `electrique`) VALUES (" + cache.systemData.temperatureValue + ", " + cache.systemData.waterLevel1 + ", " + cache.systemData.waterLevel3 + ");";

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
        else if (resultReadBuffer == 7)
        {
            resultWriteToClient = tcpServeur.sendBufferToClient(waterConso.c_str());
        }
        else if (resultReadBuffer == 8)
        {
            resultWriteToClient = tcpServeur.sendBufferToClient(electricalConso.c_str());
        }
        else if (resultReadBuffer == 0)
        {
            resultWriteToClient = tcpServeur.sendBufferToClient("Ce capteur n'existe pas");
        }

        tcpServeur.closeSocketClient();

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

void updateCache(tempMemory *cache, Capteurs capteurs, Actionneurs actionneurs, BDD bdd)
{
    srand(time(NULL));
    do
    {
        synchro.lock();
        cout << "-----------------------------------------------------" << endl;
        cout << "Mise à jour du cache ..." << endl;
        getSystemData(cache, capteurs, actionneurs, bdd);
        cout << "Temperature : " << cache->systemData.temperatureValue << endl;
        cout << "Niveau d'eau 1 : " << cache->systemData.waterLevelValue1 << endl;
        cout << "Niveau d'eau 2 : " << cache->systemData.waterLevelValue2 << endl;
        cout << "Niveau d'eau 3 : " << cache->systemData.waterLevelValue3 << endl;
        cout << "Consommation eau : " << cache->systemData.waterConsommationValue << endl;
        cout << "Consommation electrique : " << cache->systemData.electricalConsommationValue << endl;
        cout << "Etat de la pompe : " << cache->systemData.pompe << endl;
        cout << "Reseau d'eau : " << cache->systemData.eau << endl;
        cout << "Consommation eau courante : " << cache->systemData.consoEauCourante << endl;
        cout << "Consommation eau pluie : " << cache->systemData.consoEauPluie << endl;
        synchro.unlock();
        // Mettre une attente de 1 minute.
        this_thread::sleep_for(chrono::seconds(10));
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
    TCPServeur tcpServeur;
    BDD bdd;
    myServerEventListener myEventListener;
    tempMemory cache;
    Capteurs capteurs("192.168.65.120", 502);
    Actionneurs actionneurs("192.168.65.120", 502);

    tcpServeur.addListener(&myEventListener);

    if (!erreur)
    {
        thread updateCacheThread(updateCache, &cache, capteurs, actionneurs, bdd);
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
