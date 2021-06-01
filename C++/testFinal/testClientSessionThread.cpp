// Programme de test pour le thread clientSession qui permet une connexion au serveur TCP avec plusieurs client en multiThread.
// Dev by Mattei Fresi

// command to compile file -> g++ testClientSessionThread.cpp ../class/TCPServeur.cpp ../class/tempMemory.cpp -o clientThread -lpthread 

#include "../class/TCPServeur.h"
#include "../class/tempMemory.h"

using namespace std;

class myServerEventListener : public TCPServerEventListener
{
public:
    virtual void onClientConnected(SOCKET csock, SOCKADDR_IN csinIp, SOCKADDR_IN csinPort)
    {
        cout << "Un client se connecte avec la socket " << csock << " avec l'ip " << inet_ntoa(csinIp.sin_addr) << " sur le port " << htons(csinPort.sin_port) << endl;
    };
};

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

    temperature = to_string((float)cache.systemData.temperatureValue);
    waterLevel1 = to_string(cache.systemData.waterLevelValue1);
    waterLevel2 = to_string(cache.systemData.waterLevelValue2);
    waterLevel3 = to_string(cache.systemData.waterLevelValue3);
    waterConso = to_string(cache.systemData.waterConsommationValue);
    electricalConso = to_string(cache.systemData.electricalConsommationValue);
    pompe = to_string(cache.systemData.pompe);
    eau = to_string(cache.systemData.eau);

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