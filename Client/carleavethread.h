#ifndef CARLEAVETHREAD_H
#define CARLEAVETHREAD_H
#include <QDebug>
#include <QThread>
#include <opencv2/opencv.hpp>

using namespace cv;


//car leave video
class CarLeaveThread : public QThread
{
    Q_OBJECT
public:
    CarLeaveThread(char *videopath);
    void run();
private:
    VideoCapture cap;
    Mat frame;
signals:
    void frameVideo(Mat frame);
};

#endif // CARLEAVETHREAD_H
