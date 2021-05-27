#include "Actionneurs.h"
#include "ModBusTCPClient.h"
ModBusTCPClient iencli;

Actionneurs::Actionneurs(const char * addr, int port)
{   
    iencli.createSocket();
    iencli.connectSocket(addr, port);
}
int Actionneurs::SetValueElectrovanne1ON()
{
      //Trame pour temperature : 00 01 00 00 00 06 01 04 00 63 00 02.
    int ActiverElectrovanneEauPluie = iencli.sendBuffer(0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xff, 0x05, 0x00, 0xC7, 0xFF, 0x00);

    if (ActiverElectrovanneEauPluie == true)
    {
        cout << "Electrovanne eau courante bien activé" << endl;
        return 1;
    }
    else
    {
                
        cout << "Message non envoyé" << endl;
        return false;
    }
}

int Actionneurs::SetValueElectrovanne1OFF()
{
      //Trame pour temperature : 00 01 00 00 00 06 01 04 00 63 00 02.
    int ActiverElectrovanneEauPluie = iencli.sendBuffer(0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xff, 0x05, 0x00, 0xC7, 0x00, 0x00);

    if (ActiverElectrovanneEauPluie == true)
    {
        cout << "Electrovanne eau courante bien désactivé" << endl;
        return 1;
    }
    else
    {
                
        cout << "Message non envoyé" << endl;
        return false;
    }
}

