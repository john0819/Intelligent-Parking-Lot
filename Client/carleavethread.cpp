#include "carleavethread.h"

CarLeaveThread::CarLeaveThread(char *videopath)
{
    if(cap.open(videopath)) //videopath
    {
        qDebug()<<"open video error";
    }
    qRegisterMetaType<Mat>("Mat");
}

void CarLeaveThread::run()
{
    while(cap.read(frame))
    {
        emit frameVideo(frame);
        msleep(40);
    }
}
