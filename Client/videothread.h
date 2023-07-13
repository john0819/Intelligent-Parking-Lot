#ifndef VIDEOTHREAD_H
#define VIDEOTHREAD_H

#include <QThread>
#include <opencv2/opencv.hpp>

using namespace cv;


class VideoThread : public QThread
{
    Q_OBJECT
public:
    VideoThread();

    void setVideoName(QString filename);

    void setValue(int value);

protected:
    void run();

signals:
    void sendFrame2Win(Mat frame, int num);
    void send2Win_Count(double count);

public slots:
//    void getSpeed(int speed);
    void getFlag();
    void getValue(int value);
    void getSpeed(int speed);


private:
    double speed;
    unsigned long reallyspeed;
    int flag;
    int num;
    int value;
    int change;
    QString filename;
};

#endif // VIDEOTHREAD_H
