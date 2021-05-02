#include "SystemData.h"

void tempMemory::saveValueInCache(float temperature, bool waterLevel1, bool waterLevel2, bool waterLevel3,int electricalConso, bool pompe, bool eau)
{
    systemData.temperatureValue = temperature;
    systemData.waterLevelValue1 = waterLevel1;
    systemData.waterLevelValue2 = waterLevel2;
    systemData.waterLevelValue3 = waterLevel3;
    systemData.electricalConsommationValue = electricalConso;
    systemData.pompe = pompe;
    systemData.eau = eau;
}