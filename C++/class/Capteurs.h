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

class Capteurs
{
    private :  
    SOCKET sock;

    public :
    
    Capteurs(const char * addr, int port);
    ~Capteurs();
    float getTemperature();
    bool getNiveauEau();
    float getWaterconsommation();

};