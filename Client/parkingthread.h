#ifndef PARKINGTHREAD_H
#define PARKINGTHREAD_H
#include <QDebug>
#include <QThread>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

class ParkingThread : public QThread
{
    Q_OBJECT
public:
    ParkingThread(char *videopath);
    void run();
    Mat detectCarDaw(Mat frame, CascadeClassifier cascade, double scale);
private:
    VideoCapture cap;
    Mat frame;
    Mat resframe;
    CascadeClassifier cascade;

signals:
    void frameVideo(Mat frame);
};

#endif // PARKINGTHREAD_H
