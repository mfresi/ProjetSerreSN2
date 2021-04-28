#include <iostream>
#include <thread>
#include <chrono>
#include <time.h>

using namespace std;

class tempMemory
{
public:
    struct systemData
    {
        float temperatureValue = 1;
        bool waterLevelValue = 2;
        int electricalConsommationValue = 3;
    } systemData;
    //TODO créer méthode pour mettre à jour le cache avec des valeurs randoms toutes les minutes.
    void saveValueInCache(float temperature, bool waterLevel, int electricalConso);
};