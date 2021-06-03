#ifndef ACTIONNEURS_H
#define ACTIONNEURS_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <iostream>
#include "ModBusTCPClient.h"


using namespace std;

class Actionneurs {

private : 
	ModBusTCPClient clientActionneurs;
public :
	Actionneurs(const char * addr, int port);
	int SetReseauEauCourante();
	int SetReseauEauPluie();
	int SetPumpON();
	int SetPumpOFF();
};

#endif