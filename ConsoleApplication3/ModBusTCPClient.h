#pragma once
#include <winsock.h>
#include "System.h"
class ModBusTCPClient : public System
{
private :
	SOCKET sock;

public : 
	int ReadWord(int addr);
	int WriteBit(int addr, bool value);
	int WriteWord(int addr, int value);
	bool ReadBit(int addr);
	int ClientThread();
};

