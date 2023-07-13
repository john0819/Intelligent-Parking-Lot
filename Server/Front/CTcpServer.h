#pragma once
#include "CBaseSocket.h"
#include"CHostAddress.h"
#include<stdio.h>
#include<unistd.h>
#include<iostream>
using namespace std;
#define LISTEM_MAX_MUN 10
class CTcpServer :
    public CBaseSocket
{
public:
    CTcpServer(unsigned short port);
    ~CTcpServer();
    void Run();
    void Stop();
    CHostAddress* getAddress();
    void setAddress(CHostAddress* address);
private:
    CHostAddress* address;
};

