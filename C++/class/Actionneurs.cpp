#include "Actionneurs.h"



Actionneurs::Actionneurs(const char * addr, int port)
{   
    iencli.createSocket();
    iencli.connectSocket(addr, port);
}
int Actionneurs::SetReseauEauPluie()
{
 
    int ActiverElectrovanneEauPluie = iencli.sendBuffer(0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xff, 0x05, 0x00, 0xC7, 0xFF, 0x00);

    if (ActiverElectrovanneEauPluie == true)
    {
        return 1;
    }
    else
    {
        return false;
    }
}

int Actionneurs::SetReseauEauCourante()
{
    
    int ActiverElectrovanneEauPluie = iencli.sendBuffer(0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xff, 0x05, 0x00, 0xC7, 0x00, 0x00);

    if (ActiverElectrovanneEauPluie == true)
    {
        return 2;
    }
    else
    {
        return false;
    }
}

int Actionneurs::SetPumpON()
{
 
    int ActiverElectrovanneEauPluie = iencli.sendBuffer(0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xff, 0x05, 0x00, 0xC8, 0xFF, 0x00);

    if (ActiverElectrovanneEauPluie == true)
    {
        return 1;
    }
    else
    {
        return false;
    }
}

int Actionneurs::SetPumpOFF()
{
 
    int ActiverElectrovanneEauPluie = iencli.sendBuffer(0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xff, 0x05, 0x00, 0xC8, 0x00, 0x00);

    if (ActiverElectrovanneEauPluie == true)
    {
        return 1;
    }
    else
    {
        return false;
    }
}


