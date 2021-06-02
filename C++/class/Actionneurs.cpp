// Implémentation des méthodes de la classe Actionneurs.
#include "Actionneurs.h"
// Constructeur de la classe Actionneurs qui permet la connexion à la carte E/S.
Actionneurs::Actionneurs(const char * addr, int port)
{   
    clientActionneurs.createSocket();
    clientActionneurs.connectSocket(addr, port);
}
// Méthode SetReseauEauPluie qui permet d'activer l'électrovanne sur le réseau d'eau de pluie.
// Return 1 en cas de succès et false en cas d'echec.
int Actionneurs::SetReseauEauPluie()
{
 
    int ActiverElectrovanneEauPluie = clientActionneurs.sendBuffer(0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xff, 0x05, 0x00, 0xC7, 0xFF, 0x00);

    if (ActiverElectrovanneEauPluie == true)
    {
        return 1;
    }
    else
    {
        return false;
    }
}
// Méthode SetReseauEauCourante qui permet d'activer l'électrovanne sur le réseau d'eau courante.
// Return 2 en cas de succès et false en cas d'echec.
int Actionneurs::SetReseauEauCourante()
{
    
    int ActiverElectrovanneEauPluie = clientActionneurs.sendBuffer(0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xff, 0x05, 0x00, 0xC7, 0x00, 0x00);

    if (ActiverElectrovanneEauPluie == true)
    {
        return 2;
    }
    else
    {
        return false;
    }
}
// Méthode SetPumpOn qui envoie la trame à la carte E/S pour activer la pompe.
// Return 1 en cas de succès et false en cas d'echec.
int Actionneurs::SetPumpON()
{
 
    int ActiverElectrovanneEauPluie = clientActionneurs.sendBuffer(0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xff, 0x05, 0x00, 0xC8, 0xFF, 0x00);

    if (ActiverElectrovanneEauPluie == true)
    {
        return 1;
    }
    else
    {
        return false;
    }
}
// Méthode SetPimpOFF qui envoie la trame à la carte E/S pour désactiver la pompe.
// Return 1 en cas de succès et false en cas d'echec.
int Actionneurs::SetPumpOFF()
{
 
    int ActiverElectrovanneEauPluie = clientActionneurs.sendBuffer(0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0xff, 0x05, 0x00, 0xC8, 0x00, 0x00);

    if (ActiverElectrovanneEauPluie == true)
    {
        return 1;
    }
    else
    {
        return false;
    }
}


