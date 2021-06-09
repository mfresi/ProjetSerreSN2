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

   /* while (1)
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
    } */

    int waterconso = capteurs.getWaterconsommation();
    int etatWaterLevel = capteurs.getNiveauEau();
    float temperature = capteurs.getTemperature();
    int waterLevel1;
    int waterLevel2;
    int waterLevel3;
    int eau;
    int pompe;

    if (etatWaterLevel == 0)
    {
        waterLevel1 = 0;
        waterLevel2 = 0;
        waterLevel3 = 0;

        cout << "On utilise l'eau courante" << endl;
        Actionneurs.SetReseauEauCourante();
        Actionneurs.SetPumpOFF();
        pompe = 0;
        eau = 0;
    }
    else if (temperature < 2)
    {
        cout << "On utilise l'eau courante" << endl;
        Actionneurs.SetReseauEauCourante();
        eau = 0;
        pompe = 0;
    }

    else if (etatWaterLevel == 1)
    {
        waterLevel1 = 1;
        waterLevel2 = 0;
        waterLevel3 = 0;
        cout << "On active la pompe" << endl;
        Actionneurs.SetPumpON();
        pompe = 1;
    }

    else if (etatWaterLevel == 2)
    {
        waterLevel1 = 0;
        waterLevel2 = 1;
        waterLevel3 = 0;
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
        waterLevel3 = 0;
        Actionneurs.SetPumpON();
        //usleep(1500);
        cout << "on utilise l'eau de pluie" << endl;
        Actionneurs.SetReseauEauPluie();
        pompe = 1;
        eau = 1;
    }
    // Situation impossible mais on met quand meme pour ne pas avoir des valeurs randoms.
    else if (etatWaterLevel == 4)
    {
        waterLevel1 = 0;
        waterLevel2 = 0;
        waterLevel3 = 1;
    }
    // Situation impossible mais on met quand meme pour ne pas avoir des valeurs randoms.
    else if (etatWaterLevel == 5)
    {
        waterLevel1 = 1;
        waterLevel2 = 0;
        waterLevel3 = 1;
    }
    else if (etatWaterLevel == 6)
    {
        waterLevel1 = 0;
        waterLevel2 = 1;
        waterLevel3 = 1;
        eau = 1;
        pompe = 0;
        Actionneurs.SetReseauEauPluie();
        Actionneurs.SetPumpOFF();
        cout << "On utilise l'eau de pluie" << endl;
    }
    else if (etatWaterLevel == 7)
    {
        waterLevel1 = 1;
        waterLevel2 = 1;
        waterLevel3 = 1;
        cout << "on utilise l'eau de pluie" << endl;
        Actionneurs.SetPumpOFF();
        Actionneurs.SetReseauEauPluie();
        pompe = 0;
        eau = 1;
    }
       
}
