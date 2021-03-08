#pragma once
#include <winsock.h>
class TCPServeur
{
private :
	SOCKET listeningSocket();
public : 
	int ServerThread();
};

