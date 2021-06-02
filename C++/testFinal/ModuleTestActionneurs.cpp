//Pour compiler : g++ -g ModuleTestActionneurs.cpp ../class/ModBusTCPClient.cpp ../class/Actionneurs.cpp -o TestActionneurs
#include <iostream>
#include "../class/Actionneurs.h"
#include "../class/Capteurs.h"

#define SEND_DELAY 1500

using namespace std;
int main()
{
    // On se connecte sur la carte E/S.
    Actionneurs Actionneurs("192.168.65.120", 502);
    Capteurs capteurs("192.168.65.120", 502);
    bool test = false;
    // Boucle infinie.
    // On active et désactive simultanement les actionneurs pour voir si les méthodes de la classe actionneurs fonctionnent.
    while (1)
    {
        if (test)
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

    // Mise en place de l'algortihme pour choisir le réseau d'eau et activer la pompe.
   int waterconso = capteurs.getWaterconsommation();

    if (etatWaterLevel == 0)
    {
        waterLevel1 = 0;
        waterLevel2 = 0;
        cout << "On utilise l'eau courante" << endl;
        if (pompe != 1)
        {
            actionneurs.SetReseauEauCourante();
        }
        eau = 0;

        /*  if (consoEauCourante != consoEauCourante)
            {
                consoEauCourante += waterConso - consoEauCourante;
            }
            else {
                 consoEauCourante = consoEauCourante;
            } */
    }
    else if (temperature < 2)
    {
        cout << "On utilise l'eau courante" << endl;
        actionneurs.SetReseauEauCourante();
        eau = 0;
        /* if (consoEauCourante != consoEauCourante)
            {
                consoEauCourante += waterConso - consoEauCourante;
            }
            else {
                 consoEauCourante = consoEauCourante;
            } */
    }

    else if (etatWaterLevel == 1)
    {
        waterLevel1 = 1;
        waterLevel2 = 0;

        cout << "On active la pompe" << endl;
        actionneurs.SetPumpON();
        pompe = 1;
    }

    else if (etatWaterLevel == 2)
    {
        waterLevel1 = 0;
        waterLevel2 = 1;
        actionneurs.SetPumpOFF();
        //usleep(1500);
        pompe = 0;
        cout << "on utilise l'eau de pluie" << endl;
        actionneurs.SetReseauEauPluie();
        eau = 1;
        if (consoEauPluie != consoEauPluie)
        {
            consoEauPluie += waterConso - consoEauPluie;
        }
        else
        {
            consoEauPluie = consoEauPluie;
        }
    }
    else if (etatWaterLevel == 3)
    {
        waterLevel1 = 1;
        waterLevel2 = 1;
        actionneurs.SetPumpOFF();
        //usleep(1500);
        cout << "on utilise l'eau de pluie" << endl;
        actionneurs.SetReseauEauPluie();
        pompe = 0;
        eau = 1;
        // consoEauPluie = ConsoMemoire;
        ConsoMemoire = waterConso;
    }
}
