// Module de test pour mettre à jour le cache avec la librairie thread.
// Dev by mattei FRESI
#include <iostream>
#include <thread>
#include <chrono>
#include <time.h>

using namespace std;
// Initialisation de la structure systemData.
struct systemData
{
    float temperatureValue = 1;
    bool waterLevelValue = 2;
    int electricalConsommationValue = 3;

} systemData;

// Méthode saveValuInCache qui stock les dernieres valeurs enregistrées dans le cache pour les renvoyer sur le site.
// Prend en paramètre une température de type float, un niveau d'eau de type bool et une consommation électrique de type int.
void saveValueInCache(float temperature, bool waterLevel, int electricalConso)
{
    systemData.temperatureValue = temperature;
    systemData.waterLevelValue = waterLevel;
    systemData.electricalConsommationValue = electricalConso;
    // Mettre une attente de 1 minute.
    this_thread::sleep_for(chrono::seconds(1));
}

int main()
{
    int i;
    // Initialisation du random speed.
    srand(time(NULL));

    cout << "Temperature : " << systemData.temperatureValue << endl;
    cout << "niveau d'eau  : " << systemData.waterLevelValue << endl;
    cout << "Consommation électrique : " << systemData.electricalConsommationValue << endl;

    // Mise à jour 5 fois de suite le cache avec un interval de 1 seconde pour les tests.
    do
    {
        // Temperature comprise entre 0 et 10.
        float temperature = rand() % 10;
        // Niveau d'eau compris entre 0 et 1.
        int niveauEau = rand() % 2;
        // Consommation électrique comprise entre 0 et 30.
        int electricalConsommation = rand() % 30;

        saveValueInCache(temperature, niveauEau, electricalConsommation);

        cout << "Temperature : " << systemData.temperatureValue << endl;
        cout << "niveau d'eau  : " << systemData.waterLevelValue << endl;
        cout << "Consommation électrique : " << systemData.electricalConsommationValue << endl;
        i++;

    } while (i < 5);

    return 0;
}