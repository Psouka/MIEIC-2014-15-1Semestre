#ifndef SOCKET_H
#define SOCKET_H

#include <winsock2.h>
#include <iostream>

#include <exception>
#include <string>

using namespace std;

class Socket 
{
protected:
	SOCKET m_socket;
	bool active;
public:
	Socket();
	~Socket();
	bool isActive();

	string sendMessage(string message);
};


#endif