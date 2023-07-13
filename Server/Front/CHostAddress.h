#pragma once
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
class CHostAddress
{
public:
	CHostAddress(unsigned short port);
	~CHostAddress();
	unsigned short getPort();
	void setPort(unsigned short port);
	struct sockaddr_in getAddr_in();
	struct sockaddr* getAddr();
	int getLength();
private:
	unsigned short port;
	struct sockaddr_in s_addr;
	int length;
};

