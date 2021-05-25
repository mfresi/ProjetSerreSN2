#include "Capteurs.h"

ModBusTCPClient Client;

Capteurs::Capteurs(const char *addr, int port)
{
    Client.createSocket();
    Client.connectSocket(addr, port);
}

Capteurs::~Capteurs()
{
}

float Capteurs::getTemperature()
{

    //Trame pour temperature : 00 01 00 00 00 06 01 04 00 63 00 02.
    int resultgetTemperature = Client.sendBuffer(0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x01, 0x04, 0x00, 0x63, 0x00, 0x02);

    if (resultgetTemperature == true)
    {
        cout << "trame pour temperature OK" << endl;
        float temperature = Client.recvTemperature();

        if (temperature)
        {
            cout << "Temperature exterieure : " << temperature << " °C" << endl;
        }
        else
        {
            cout << "Pas réussi à envoyer trame pour temperature" << endl;
        }
    }
    else
    {
        cout << "Pas réussi à envoyer la trame" << endl;
    }
}

bool Capteurs::getNiveauEau()
{
    int resultgetWaterLevel = Client.sendBuffer(0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x01, 0x02, 0x00, 0x63, 0x00, 0x02);

    if (resultgetWaterLevel == true)
    {
        int waterLevel = Client.recvWaterLevel();

        if (waterLevel == 0)
        {
            cout << "Etat niveau d'eau : 0" << endl;
            
        }
        else
        {
            cout << "Etat niveau d'eau : " << waterLevel << endl;
          
        }
    }
}

float Capteurs::getWaterconsommation()
{

    return 0;
}