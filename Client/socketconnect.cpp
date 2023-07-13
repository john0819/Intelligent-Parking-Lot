#include "socketconnect.h"

SocketConnect * SocketConnect::sc = nullptr;

SocketConnect *SocketConnect::getInstance()
{
    if(SocketConnect::sc == nullptr)
    {
        SocketConnect::sc = new SocketConnect();
    }
    return SocketConnect::sc;

}

//connect the server
void SocketConnect::CreateConnect()
{
    if(socketfd == -1)
    {
        perror("socket error");
    }
    else
    {
        s_addr.sin_family=AF_INET;
        s_addr.sin_port=htons(this->host_address);
        s_addr.sin_addr.s_addr=inet_addr(this->ip_address.toStdString().c_str());
        len=sizeof(s_addr);

        if(connect(socketfd,(struct sockaddr*)&s_addr,len)==-1)
        {
            perror("connect error");
        }
        //successful connect server
        this->flag =1;
    }
}

void SocketConnect::close()
{
    if(socketfd == -1)
    {
        perror("socket error");
    }
    else {

    }
}

int SocketConnect::getSocketfd() const
{
    return this->socketfd;
}

void SocketConnect::setSocketfd(int value)
{
    this->socketfd = value;
}

void SocketConnect::setHost(int host)
{
    this->host_address =(unsigned short) host;
}

void SocketConnect::setIp(QString ip)
{
    this->ip_address = ip;
}

int SocketConnect::getFlag()
{
    return this->flag;
}

SocketConnect::SocketConnect()
{
    //prepare for the connect
    this->socketfd = socket(AF_INET, SOCK_STREAM, 0);
    this->len = sizeof(s_addr);
    this->flag = 0; //judge whether connect server
}
