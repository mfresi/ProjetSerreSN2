#pragma once
#include "System.h"
class BDD : public System
{
public : 
	int SaveSystemData(SystemData);
	BDD(int host,int port,char pass,int bdd);
	int ServerThread();
	
};

