#ifndef CARENTERTHREAD_H
#define CARENTERTHREAD_H
#include <QDebug>
#include <QThread>
#include <opencv2/opencv.hpp>

using namespace cv;


class CarEnterThread : public QThread
{
    Q_OBJECT
public:
    CarEnterThread(char *videopath);
    void run();
private:
    VideoCapture cap;
    Mat frame;
signals:
    void frameVideo(Mat frame);
};

#endif // CARENTERTHREAD_H
