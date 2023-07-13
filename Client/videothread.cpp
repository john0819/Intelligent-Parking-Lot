#include "videothread.h"
#include <QDebug>

VideoThread::VideoThread()
{
    this->speed=1;
    this->flag=1;
    this->num=0;
    this->value=0;
    this->change=0;
    this->reallyspeed = 40;
    qRegisterMetaType<Mat>("Mat");
}

void VideoThread::setVideoName(QString filename)
{
    qDebug()<<"setVideoName filename = "<<filename;
    this->filename = filename;
}

//set value
void VideoThread::setValue(int value)
{
    qDebug()<<"VideoThread::setValue = "<<value;
    this->value = value;
    this->change =1;
}

void VideoThread::run()
{
    Mat frame;
    //VideoCapture cap("./Video/carMove.mp4");
    VideoCapture cap(filename.toStdString().c_str());
    //count of video
    double frame_num = cap.get(7);
    qDebug()<<"frame_num"<<frame_num;
    emit send2Win_Count(frame_num);

    while(cap.read(frame))
    {
        while(this->flag%2 == 0) //stop
        {

        }
        if(this->change==1)
        {
            cap.set(CAP_PROP_POS_FRAMES,this->value); //change process of video
            this->change=0;
            this->num=this->value;
        }

        num++;
        emit sendFrame2Win(frame,num);
        msleep(reallyspeed);
    }
}

void VideoThread::getFlag()
{
    this->flag++;
}

void VideoThread::getValue(int value)
{
    this->value = value;
    this->change=1;
}

void VideoThread::getSpeed(int speed)
{
    switch(speed)
    {
    case 0:
            this->speed=1;
            break;
    case 1:
            this->speed=1.5;
            break;
    case 2:
            this->speed=2;
            break;
    }
    qDebug()<<this->speed;

    reallyspeed = (unsigned long)(40/this->speed);

}
