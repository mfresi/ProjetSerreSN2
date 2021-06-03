//Pour compiler : g++ -g ModuleTestActionneurs.cpp ../class/ModBusTCPClient.cpp ../class/Actionneurs.cpp ../class/Capteurs.cpp -o TestActionneurs
#include <iostream>
#include "../class/Actionneurs.h"
#include "../class/Capteurs.h"

using namespace std;
int main()
{
    //ModBusTCPClient test;
    Actionneurs Actionneurs("192.168.65.120", 502);
    Capteurs capteurs("192.168.65.120", 502);
    bool test = false;

    while (1)
    {
        if (test)
        {
            Actionneurs.SetPumpON();
            Actionneurs.SetReseauEauPluie();
            cout << "on utilise l'eau de pluie et on allume la pompe" << endl;
        }
        else
        {
            Actionneurs.SetPumpOFF();
            Actionneurs.SetReseauEauCourante();
            cout << "on utilise l'eau courante et on éteint la pompe" << endl;
        }
        test = !test;
        sleep(1);
    }

    int waterconso = capteurs.getWaterconsommation();
    int etatWaterLevel = capteurs.getNiveauEau();
    float temperature = capteurs.getTemperature();
    int waterLevel1;
    int waterLevel2;
    int eau;
    int pompe;
/*
    if (etatWaterLevel == 0)
    {
        waterLevel1 = 0;
        waterLevel2 = 0;
        cout << "On utilise l'eau courante" << endl;
        if (pompe != 1)
        {
            Actionneurs.SetReseauEauCourante();
        }
        eau = 0;
    }
    else if (temperature < 2)
    {
        cout << "On utilise l'eau courante" << endl;
        Actionneurs.SetReseauEauCourante();
        eau = 0;
    }

    else if (etatWaterLevel == 1)
    {
        waterLevel1 = 1;
        waterLevel2 = 0;

        cout << "On active la pompe" << endl;
        Actionneurs.SetPumpON();
        pompe = 1;
    }

    else if (etatWaterLevel == 2)
    {
        waterLevel1 = 0;
        waterLevel2 = 1;
        Actionneurs.SetPumpOFF();
        //usleep(1500);
        pompe = 0;
        cout << "on utilise l'eau de pluie" << endl;
        Actionneurs.SetReseauEauPluie();
        eau = 1;
    }
    else if (etatWaterLevel == 3)
    {
        waterLevel1 = 1;
        waterLevel2 = 1;
        Actionneurs.SetPumpOFF();
        //usleep(1500);
        cout << "on utilise l'eau de pluie" << endl;
        Actionneurs.SetReseauEauPluie();
        pompe = 0;
        eau = 1;
        // consoEauPluie = ConsoMemoire;
       
       
    }*/
}
