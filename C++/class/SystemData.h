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
        float temperatureValue;
        bool waterLevelValue1;
        bool waterLevelValue2;
        bool waterLevelValue3;
        float waterConsommationValue;
        int electricalConsommationValue;
        bool pompe;
        bool eau;
    } systemData;
    void refreshSystemState(float temperature, bool waterLevel1, bool waterLevel2, bool waterLevel3, float waterConsommation, int electricalConsommation, bool pompe, bool eau);
};