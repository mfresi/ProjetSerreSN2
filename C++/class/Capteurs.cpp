// Implémentation des méthodes de la classe Capteurs.
#include "Capteurs.h"
#include "ModBusTCPClient.h"
ModBusTCPClient Client;
// Constructeur qui permet la connexion à la carte E/S.
Capteurs::Capteurs(const char *addr, int port)
{
    Client.createSocket();
    Client.connectSocket(addr, port);
}

Capteurs::~Capteurs()
{
}
// Méthode qui permet de récupérer la valeur du capteur de température.
// Return la temperature en cas de succès et false en cas d'echec.
float Capteurs::getTemperature()
{

    //Trame pour temperature : 00 01 00 00 00 06 01 04 00 63 00 02.
    int resultgetTemperature = Client.sendBuffer(0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x01, 0x04, 0x00, 0x63, 0x00, 0x02);

    if (resultgetTemperature == true)
    {
        // Méthode qui permet le traitement de la trame de réception pour la valeur du capteur de température.
        float temperature = Client.recvTemperature();

        if (temperature)
        {
            return temperature;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return false;
    }
}
// Méthode qui permet de récupérer l'état des capteurs de niveau d'eau.
// Return la valeur de l'etat des capteurs de niveau d'eau en cas de succèset -1 en cas d'echec.
int Capteurs::getNiveauEau()
{
    int resultgetWaterLevel = Client.sendBuffer(0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x01, 0x02, 0x00, 0x63, 0x00, 0x03);

    if (resultgetWaterLevel == true)
    {
        // Méthode qui traite la trame de réception des capteurs de niveau d'eau.
        int waterLevel = Client.recvWaterLevel();

        if (waterLevel == 0)
        {
            return 0; 
        }
        else if (waterLevel == 1)
        {
            return 1;
        }
        else if (waterLevel == 2)
        {
            return 2;
        }
        else if (waterLevel == 3)
        {
            return 3;
        }
        else if (waterLevel == 4)
        {
            return 4;
        }
        else if (waterLevel == 5)
        {
            return 5;
        }
        else if (waterLevel == 6)
        {
            return 6;
        }
        else if (waterLevel == 7)
        {
            return 7;
        }
    }
        return -1;
}
// Méthode pour récupérer le nombre d'impulsion du capteur de consommation d'eau.
// Return la valeur de la consommation électrique en vas de succès et false en cas d'echec.
float Capteurs::getWaterconsommation()
{

     int resultgetTemperature = Client.sendBuffer(0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x01, 0x04, 0x00, 0xCD, 0x00, 0x01);

    if (resultgetTemperature == true)
    {
        float WaterConso = Client.recvWaterConso();

        if (WaterConso)
        {
            return WaterConso;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return false;
    }

}