#pragma once
#include "SystemData.h"
class System : public SystemData
{
public : 
	int SystemThread;

	int getSystemData();
	int RefreshSystemState();
};

