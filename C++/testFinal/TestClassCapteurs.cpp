#include "../class/Capteurs.h"
//Compilation sous linux
//g++ -g TestClassCapteurs.cpp ../class/Capteurs.cpp ../class/ModBusTCPClient.cpp -o TestCapteurs


int main()
{
    float temperature;
    int niveauEau;
    float WaterConso;
    Capteurs capteurs("192.168.65.120",502);

    temperature = capteurs.getTemperature();

    niveauEau = capteurs.getNiveauEau();
    WaterConso = capteurs.getWaterconsommation();

    cout << "Temperature : " << temperature << " °C" << endl;
    cout << "Etat niveau d'eau : " << niveauEau << endl;
    cout << "La consommation d'eau est de : " << WaterConso << " Litres"<< endl;
}