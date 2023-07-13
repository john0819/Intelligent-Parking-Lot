#include "writethread.h"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

WriteThread* WriteThread::writethread = nullptr;

WriteThread *WriteThread::getInstance()
{
    if(WriteThread::writethread == nullptr)
    {
        WriteThread::writethread = new WriteThread();

    }
    return WriteThread::writethread;
}

void WriteThread::run()
{
    while(1)
    {
        if(this->length > 0)
        {
            int res = write(this->socketfd, this->data, this->length);
            qDebug()<<res;
            bzero(this->data,sizeof(this->data));
            this->length = 0;
        }
    }
}


void WriteThread::setData(void *value, int size)
{
    /*
    REGISTER reg;
    char buf4[3000]={0};
    memcpy(buf4,value,size);

    //<<<>>>
    char buf3[3000]={0};

    //head
    HEAD head;
    memset(&head,0,sizeof(head));
    memcpy(&head, buf4, sizeof(HEAD));

    //struct
    char buf2[head.bussinesslen];
    memset(buf2, 0 ,sizeof(buf2));
    memcpy(buf2, buf4+sizeof(head), sizeof(head.bussinesslen));
    head .CRC = this->CalcCRCCode((unsigned char *)buf2, head.bussinesslen);
    //new buf
    memcpy(buf3,&head,sizeof(head));
    memcpy(buf3+sizeof(head), buf2, sizeof(buf2));
    */
    this->length = size;
    memcpy(this->data, value, size);
    //restart
    this->restartTimer();
}

void WriteThread::setSocketfd(int fd)
{
    this->socketfd = fd;
}

unsigned int WriteThread::CalcCRCCode(unsigned char *Array, unsigned int Len)
{
    unsigned int i = 0;
        unsigned int j = 0;
        const unsigned short CalcConst = 0xFFFF;
        unsigned int TempOut = 0;
        for (i = 0; i < Len; i++)
        {
            TempOut = CalcConst ^ Array[i];
            for (j = 0; j < 8; j++)
            {
                if (TempOut & 0x0001)
                {
                    TempOut = TempOut >> 1;
                    TempOut ^= 0xA001;
                }
                else {
                    TempOut = TempOut >> 1;
                }
            }
        }
        return(TempOut);
}

void WriteThread::restartTimer()
{
    this->timer->stop();
    timer->start(300000);
}

//donot operate, so log out
void WriteThread::logout()
{
    char res[1024]={0};
    memset(&this->head,0,sizeof(this->head));
    this->head.bussinesstype=23;
    this->head.CRC=shareinfo->CalcCRCCode((unsigned char*)res, 0);
    this->head.bussinesslen=0;
    memset(this->buf,0,sizeof(this->buf));
    memcpy(this->buf,&(this->head),sizeof(this->head));
    this->setData(buf,sizeof(this->head));
    qDebug()<<"type =23, log out!!";
}

WriteThread::WriteThread()
{
    this->length = 0;
    this->flag=0;
    memset(this->data,0,sizeof(this->data));

    this->shareinfo = ShareInfo::getInstance();

    timer = new QTimer(this);
    connect(this->timer,SIGNAL(timeout()),this,SLOT(logout()));
    timer->start(300000); //1s 1000 5min=300s

}
