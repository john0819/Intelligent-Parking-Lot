#include "mythread.h"
#include <QDebug>

//open window video

MyThread::MyThread(QObject *parent)
{
    qRegisterMetaType<Mat>("Mat");
}

void MyThread::run()
{
    Mat frame;
    VideoCapture cap("./Video/HarmonyOS.mp4");
    while(cap.read(frame))
    {
        emit Send2Widget(frame);
        msleep(40);
    }
    emit Sendchange();
}
