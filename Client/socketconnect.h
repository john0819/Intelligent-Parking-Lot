#ifndef SOCKETCONNECT_H
#define SOCKETCONNECT_H

#include <iostream>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <QString>

class SocketConnect
{
public:
    static SocketConnect * sc;
    static SocketConnect *getInstance();

    void CreateConnect();
    void close();

    int getSocketfd() const;
    void setSocketfd(int value);

    //set some
    void setHost(int host);
    void setIp(QString ip);

    int getFlag();

private:
    SocketConnect();
    struct sockaddr_in s_addr;
    int socketfd;
    int len;
    QString ip_address;
    unsigned short host_address;
    int flag;
};

#endif // SOCKETCONNECT_H
