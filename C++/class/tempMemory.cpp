#include "tempMemory.h"

void tempMemory::refreshSystemState(float temperature, bool waterLevel1, bool waterLevel2, bool waterLevel3, float waterConsommation, int electricalConsommation, bool pompe, bool eau, int consoEauCourante, int consoEauPluie)
{
    systemData.temperatureValue = temperature;
    systemData.waterLevelValue1 = waterLevel1;
    systemData.waterLevelValue2 = waterLevel2;
    systemData.waterLevelValue3 = waterLevel3;
    systemData.waterConsommationValue = waterConsommation;
    systemData.electricalConsommationValue = electricalConsommation;
    systemData.pompe = pompe;
    systemData.eau = eau;
    systemData.consoEauCourante = consoEauCourante;
    systemData.consoEauPluie = consoEauPluie;
}