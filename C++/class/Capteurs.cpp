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

int Capteurs::getNiveauEau()
{
    int resultgetWaterLevel = Client.sendBuffer(0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x01, 0x02, 0x00, 0x63, 0x00, 0x02);

    if (resultgetWaterLevel == true)
    {
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
    }
}

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