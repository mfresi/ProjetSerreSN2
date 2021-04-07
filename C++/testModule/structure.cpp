// Module de test pour la mise en cache des valeurs des capteurs.
// Dev by mattei FRESI

#include <iostream>
#include <unistd.h>

using namespace std;

// Initialisation de la structure dataCache qui va garder en mémoire les dernières valeurs relevées.
struct dataCache
{
    float temperatureValue = 22.5;
    bool waterLevelValue = 1;
    int electricalConsommationValue = 14;
    
} dataCache;

// Méthode saveValuInCache qui stock les dernieres valeurs enregistrées dans le cache pour les renvoyer sur le site.
// Prend en paramètre une température de type float, un niveau d'eau de type bool et une consommation électrique de type int.
void saveValueInCache(float temperature, bool waterLevel, int electricalConso)
{
    dataCache.temperatureValue = temperature;
    dataCache.waterLevelValue = waterLevel;
    dataCache.electricalConsommationValue = electricalConso;
}

int main()
{
    cout << "Valeur de la température : " << dataCache.temperatureValue << endl;
    cout << "Valeur du niveau d'eau : " << dataCache.waterLevelValue << endl;
    cout << "Valeur de la consommation electrique : " << dataCache.electricalConsommationValue << endl;

    saveValueInCache(18, 0, 45);

    // Pause d'une minute entre chaque insertion dans le cache.
    sleep(60);

    cout << "Valeur de la température : " << dataCache.temperatureValue << endl;
    cout << "Valeur du niveau d'eau : " << dataCache.waterLevelValue << endl;
    cout << "Valeur de la consommation electrique : " << dataCache.electricalConsommationValue << endl;

    return 0;
}