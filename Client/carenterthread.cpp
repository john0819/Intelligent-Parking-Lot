#include "carenterthread.h"

CarEnterThread::CarEnterThread(char *videopath)
{
    if(cap.open(videopath)) //videopath
    {
        qDebug()<<"open video error";
    }
    qRegisterMetaType<Mat>("Mat");
}

void CarEnterThread::run()
{
    while(cap.read(frame))
    {
        emit frameVideo(frame);
        msleep(40);
    }

}
