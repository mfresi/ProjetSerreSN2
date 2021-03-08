#pragma once
#include "SystemData.h"
class Actionneurs : public SystemData
{

private : 
	bool value;
	int addr;

public :
	Actionneurs(int addr);
	int SetValue(bool value);
	float Temperature();

};

