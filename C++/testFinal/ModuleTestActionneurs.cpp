//Pour compiler : g++ -g ModuleTestActionneurs.cpp ../class/ModBusTCPClient.cpp ../class/Actionneurs.cpp -o TestActionneurs
#include <iostream>
#include "../class/SystemData.h"
#include "../class/Capteurs.h"
#include "../class/Actionneurs.h"
#include "../class/ModBusTCPClient.h"

#define SEND_DELAY 1500

using namespace std;
int main()
{
    //ModBusTCPClient test;
    Actionneurs Actionneurs("192.168.65.120",502);
    bool test = false;

    while(1)
    {
        if(test)
        {
            Actionneurs.SetPumpON();
            usleep(SEND_DELAY);
            Actionneurs.SetReseauEauPluie();
        }
        else
        {
            Actionneurs.SetPumpOFF();
            usleep(SEND_DELAY);
            Actionneurs.SetReseauEauCourante();
        }
        test = !test;
        sleep(1);
    }
    
}
 