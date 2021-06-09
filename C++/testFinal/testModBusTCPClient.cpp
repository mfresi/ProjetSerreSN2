#include "../class/ModBusTCPClient.h"

// Command to compile -> g++ -g testModBusTCPClient.cpp ../class/ModBusTCPClient.cpp -o modbusClient

using namespace std;

int main()
{
    ModBusTCPClient modbus;

    int resultCreateSocket = modbus.createSocket();

    if (resultCreateSocket == true)
    {
        cout << "Socket créé" << endl;
        int resultConnexionToCard = modbus.connectSocket("192.168.65.120", 502);

        if (resultConnexionToCard == true)
        {
            cout << "Connexion à la carte réussi" << endl;
            int resultgetTemperature = modbus.sendBuffer(0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x01, 0x04, 0x00, 0x63, 0x00, 0x02);

            if (resultgetTemperature == true)
            {
                float temperature = modbus.recvTemperature();

                if (temperature)
                {
                    cout << "Temperature exterieure : " << temperature << " °C" << endl;
                }
                else
                {
                    cout << "Pas de temperature" << endl;
                }
            }
            else
            {
                cout << "Pas réussi à envoyer la trame" << endl;
            }

            int resultgetWaterLevel = modbus.sendBuffer(0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x01, 0x02, 0x00, 0x63, 0x00, 0x03);

            if (resultgetWaterLevel == true)
            {
                int waterLevel = modbus.recvWaterLevel();

                cout << "Valeur du waterLevel : " << waterLevel << endl;

                if (waterLevel == -1)
                {
                    cout << "Pas réussi à lire la valeur du capteur" << endl;
                }
                else if (waterLevel == 0)
                {
                    //Les deux capteurs à 0
                    cout << "les trois capteurs de niveau d'eau sont à l'etat 0" << endl;
                }
                else if (waterLevel == 1)
                {
                    //Le capeur métal est 1 et plastique 0
                    cout << "Capteur de la cuve de récupération d'eau de pluie est à 1" << endl;
                    cout << "Capteur du bas de la cuve d'alimentation du système est à 0" << endl;
                    cout << "Capteur du haut de la cuve d'alimentation du système est à 0" << endl;
                }
                else if (waterLevel == 2)
                {
                    //Le capteur metal est 0 et plastique 1
                    cout << "Capteur de la cuve de récupération d'eau de pluie est à 0" << endl;
                    cout << "Capteur cuve du bas d'alimentation du système est à 1" << endl;
                    cout << "Capteur du haut de la cuve d'alimentation du système est à 0" << endl;
                }
                else if (waterLevel == 3)
                {
                    //Les deux capteurs à 1
                    cout << "Capteur de la cuve de récupération d'eau de pluie est à 1" << endl;
                    cout << "Capteur cuve du bas d'alimentation du système est à 1" << endl;
                    cout << "Capteur du haut de la cuve d'alimentation du système est à 0" << endl;
                }
                else if (waterLevel == 4)
                {
                    cout << "Capteur de la cuve de récupération d'eau de pluie est à 0" << endl;
                    cout << "Capteur cuve du bas d'alimentation du système est à 0" << endl;
                    cout << "Capteur du haut de la cuve d'alimentation du système est à 1" << endl;
                }
                else if (waterLevel == 5)
                {
                    cout << "Capteur de la cuve de récupération d'eau de pluie est à 1" << endl;
                    cout << "Capteur cuve du bas d'alimentation du système est à 0" << endl;
                    cout << "Capteur du haut de la cuve d'alimentation du système est à 1" << endl;
                }
                else if (waterLevel == 6)
                {
                    cout << "Capteur de la cuve de récupération d'eau de pluie est à 0" << endl;
                    cout << "Capteur cuve du bas d'alimentation du système est à 1" << endl;
                    cout << "Capteur du haut de la cuve d'alimentation du système est à 1" << endl;
                }
                else if (waterLevel == 7)
                {
                    cout << "les trois capteurs de niveau d'eau sont à l'etat 1" << endl;
                }
            }
            else
            {
                cout << "Pas réussi à envoyer la trame pour temperature" << endl;
            }
        }
        else
        {
            cout << "Pas réussi à se connecter à la carte" << endl;
        }
    }
    else
    {
        cout << "Pas réussi à créer le socket" << endl;
    }
}