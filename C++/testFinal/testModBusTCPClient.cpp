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
            //Trame pour temperature : 00 01 00 00 00 06 01 04 00 63 00 02.
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

            int resultgetWaterLevel = modbus.sendBuffer(0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x01, 0x02, 0x00, 0x63, 0x00, 0x02);

            if (resultgetWaterLevel == true)
            {
                int waterLevel = modbus.recvWaterLevel();

                if (waterLevel == 0)
                {
                    cout << "Etat niveau d'eau : 0" << endl;
                    return 0;
                }
                else
                {
                    cout << "Etat niveau d'eau : " << waterLevel << endl;
                    return 1;
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