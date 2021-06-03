// Déclaration de la classe Capteurs.
// Dev by Fresi.
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


using namespace std;

class Capteurs
{
    private :  


    public :
    
    Capteurs(const char * addr, int port);
    ~Capteurs();
    float getTemperature();
    int getNiveauEau();
    float getWaterconsommation();

};