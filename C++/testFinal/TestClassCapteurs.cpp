#include "../class/Capteurs.h"

int main()
{
    float temperature;
    int niveauEau;
    Capteurs capteurs("192.168.65.120",502);

    temperature = capteurs.getTemperature();

    niveauEau = capteurs.getNiveauEau();

    cout << "Temperature : " << temperature << " °C" << endl;
    cout << "Etat niveau d'eau : " << niveauEau << endl;
}