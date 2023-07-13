#include "CHostAddress.h"

CHostAddress::CHostAddress(unsigned short port)
{
    this->port = port;
    this->s_addr.sin_family = AF_INET;
    this->s_addr.sin_port = htons(this->port);
    this->s_addr.sin_addr.s_addr = INADDR_ANY;
    this->length = sizeof(this->s_addr);
}

CHostAddress::~CHostAddress()
{
}

unsigned short CHostAddress::getPort()
{
    return this->port;
}

void CHostAddress::setPort(unsigned short port)
{
    this->port = port;
}

sockaddr_in CHostAddress::getAddr_in()
{
    return this->s_addr;
}

sockaddr* CHostAddress::getAddr()
{
    return (struct sockaddr*)&(this->s_addr);
}

int CHostAddress::getLength()
{
    return this->length;
}