//Module de test pour mettre à jour les valeurs des capteurs et actionneurs dans l'objet SystemData.
//Dev by Mattei Fresi

//Commande pour compiler -> g++ testupdateCacheThread.cpp ../class/tempMemory.cpp ../class/TCPServeur.cpp ../class/Capteurs.cpp ../class/Actionneurs.cpp ../class/ModBusTCPClient.cpp -o updateCache -lpthread 

#include "../class/tempMemory.h"
#include "../class/TCPServeur.h"
#include "../class/Capteurs.h"
#include "../class/Actionneurs.h"

void getSystemData(tempMemory *cache, Capteurs capteurs, Actionneurs actionneurs)
{
    float temperature = capteurs.getTemperature();
    int etatWaterLevel = capteurs.getNiveauEau();
    int waterConso = capteurs.getWaterconsommation();
    bool waterLevel1;
    bool waterLevel2;
    bool pompe;
    bool eau;
    int ElectricalConso = rand() % 30;
    bool waterLevel3 = 0;
    int eauCourante = 0;
    int eauPluie = 0;

    if (etatWaterLevel == 0)
    {
        waterLevel1 = 0;
        waterLevel2 = 0;
        cout << "On utilise l'eau courante" << endl;
        if (pompe == 1)
        {
             actionneurs.SetReseauEauCourante();
             actionneurs.SetPumpOFF();
             pompe = 0;
        }
        eau = 0;
    }
    else if (temperature < 2)
    {
        cout << "On utilise l'eau courante" << endl;
        actionneurs.SetReseauEauCourante();
        eau = 0;
    }

    else if (etatWaterLevel == 1)
    {
        waterLevel1 = 1;
        waterLevel2 = 0;
       
            cout << "On active la pompe" << endl;
            actionneurs.SetPumpON();
            pompe = 1;
            eau = 1;
    }

    else if (etatWaterLevel == 2)
    {
        waterLevel1 = 0;
        waterLevel2 = 1;
        cout << "On désactive la pompe" << endl;
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
    // Met à jour la valeur du cache SystemData avec les valeurs aléatoires pour le module de test.
    cache->refreshSystemState(temperature, waterLevel1, waterLevel2, waterLevel3, waterConso, ElectricalConso, pompe, eau, eauCourante, eauPluie);
}

void updateCache(tempMemory *cache, Capteurs capteurs, Actionneurs actionneurs)
{
    srand(time(NULL));
    do
    {
        cout << "Mise à jour du cache ..." << endl;
        getSystemData(cache, capteurs, actionneurs);
        cout << "Temperature : " << cache->systemData.temperatureValue << endl;
        cout << "Niveau d'eau 1 : " << cache->systemData.waterLevelValue1 << endl;
        cout << "Niveau d'eau 2 : " << cache->systemData.waterLevelValue2 << endl;
        cout << "Consommation electrique : " << cache->systemData.electricalConsommationValue << endl;
        cout << "Etat de la pompe : " << cache->systemData.pompe << endl;
        cout << "Reseau d'eau : " << cache->systemData.eau << endl;
        cout << "Consommation eau courant : " << cache->systemData.consoEauCourante << endl;
        cout << "Consommation eau pluie : " << cache->systemData.consoEauPluie << endl;
        cout << "-------------------------------------" << endl;
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
    tempMemory cache;
    Capteurs capteurs("192.168.65.120", 502);
    Actionneurs actionneurs("192.168.65.120", 502);

    if (!erreur)
    {
        thread updateCacheThread(updateCache, &cache, capteurs, actionneurs);
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