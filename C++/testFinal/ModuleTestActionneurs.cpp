//Pour compiler : g++ -g ModuleTestActionneurs.cpp ../class/ModBusTCPClient.cpp ../class/Actionneurs.cpp -o TestActionneurs
#include <iostream>
#include "../class/SystemData.h"
#include "../class/Capteurs.h"
#include "../class/Actionneurs.h"
#include "../class/ModBusTCPClient.h"
using namespace std;
int main()
{
    //ModBusTCPClient test;
    Actionneurs Actionneurs("192.168.65.120",502);
    
    Actionneurs.SetPumpOFF();
    sleep(1);
    Actionneurs.SetReseauEauCourante();
    
    getchar();
}
 