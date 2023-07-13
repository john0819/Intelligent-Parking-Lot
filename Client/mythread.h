#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QThread>

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);

protected:
    void run();

signals:
    void Send2Widget(Mat frame);
    void Sendchange();


};

#endif // MYTHREAD_H
