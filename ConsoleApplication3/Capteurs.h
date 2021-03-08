#pragma once
#include "SystemData.h"
class Capteurs : public SystemData
{
private : 
	int addr;
	//type type;
	bool Bool_Value;
	float Float_Value;
	int Int_Value;

public : 
	Capteurs();
	~Capteurs();
	int getTemp(int addr, int type);
	int getNiveauEau(int addr, bool type);
	int getWaterConsommation(int addr, float type);
};

