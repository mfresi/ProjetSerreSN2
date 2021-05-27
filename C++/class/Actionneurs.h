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

class Actionneurs {

private : 
	
public :
	Actionneurs(const char * addr, int port);
	int SetValueElectrovanne1ON();
	int SetValueElectrovanne1OFF();

};