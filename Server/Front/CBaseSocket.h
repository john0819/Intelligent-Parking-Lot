#pragma once
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include<stdio.h>
class CBaseSocket
{
public:
	CBaseSocket(unsigned short port);
	~CBaseSocket();
	void Start();
	virtual void Run() = 0;
	virtual void Stop() = 0;
	int getSocketfd();
protected:
	int socketfd;
};



