#include "SystemData.h"

void tempMemory::saveValueInCache(float temperature, bool waterLevel, int electricalConso)
{
    systemData.temperatureValue = temperature;
    systemData.waterLevelValue = waterLevel;
    systemData.electricalConsommationValue = electricalConso;
    // Mettre une attente de 1 minute.
    this_thread::sleep_for(chrono::seconds(1));
}