#include "../class/Capteurs.h"

int main()
{
    Capteurs capteurs("192.168.65.120",502);

    capteurs.getTemperature();

    capteurs.getNiveauEau();
}