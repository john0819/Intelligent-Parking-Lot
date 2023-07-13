#include "CTcpServer.h"

CTcpServer::CTcpServer(unsigned short port) :CBaseSocket(port)
{
	this->address = new CHostAddress(port);

}

CTcpServer::~CTcpServer()
{
}

void CTcpServer::Run()
{
	int opt_val = 1;
	if (setsockopt(this->socketfd, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof(opt_val)))
	{
		perror("setsockopt error");
	}
	if (bind(this->socketfd, this->address->getAddr(), this->address->getLength()) == -1)
	{
		perror("bind error");
	}
	if (listen(this->socketfd, LISTEM_MAX_MUN) == -1)
	{
		perror("listen error");
	}
	cout << "Server start success socketfd=" << this->socketfd << endl;
}

void CTcpServer::Stop()
{
	if (this->socketfd != 0)
	{
		close(this->socketfd);
		this->socketfd = 0;
	}
}

CHostAddress* CTcpServer::getAddress()
{
	return this->address;
}

void CTcpServer::setAddress(CHostAddress* address)
{
	this->address = address;
}