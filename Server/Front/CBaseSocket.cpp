#include "CBaseSocket.h"

CBaseSocket::CBaseSocket(unsigned short port)
{
    this->socketfd = 0;
}

CBaseSocket::~CBaseSocket()
{
}

void CBaseSocket::Start()
{
    this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->socketfd < 0)
    {
        perror("socket error");
    }
    this->Run();
}

int CBaseSocket::getSocketfd()
{
    return this->socketfd;
}

