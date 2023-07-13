#ifndef WRITETHREAD_H
#define WRITETHREAD_H

#include "protocol.h"
#include <QDebug>
#include "QThread"
#include <QTimer>
#include "shareinfo.h"

class WriteThread : public QThread
{
    Q_OBJECT
public:
    static WriteThread * writethread;
    static WriteThread * getInstance();

    void run();
    void setData(void *value, int size);
    void setSocketfd(int fd);

    unsigned int CalcCRCCode(unsigned char *Array, unsigned int Len);

    void restartTimer();

public slots:
    void logout();
private:
    WriteThread();

    int socketfd;
    char data[3000];
    int length;
    QTimer *timer;
    int flag;

    HEAD head;
    char buf[1024];

    ShareInfo *shareinfo;
};

#endif // WRITETHREAD_H
