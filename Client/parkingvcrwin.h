#ifndef PARKINGVCRWIN_H
#define PARKINGVCRWIN_H

#include <QWidget>
#include <parkingthread.h>
#include <shareinfo.h>
#include <QTimer>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include "readthread.h"
#include "writethread.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

using namespace cv;

using namespace std;

namespace Ui {
class ParkingVCRWin;
}

class ParkingVCRWin : public QWidget
{
    Q_OBJECT

public:
    explicit ParkingVCRWin(QWidget *parent = nullptr);
    ~ParkingVCRWin();
    void clearQueue(queue<Mat> &que);

    void StartThread();

    void SetFrameSize(QString filename);

    void SavePicture(QString filename);

    void Send2Server();

    void startVideo();

protected:
    void paintEvent(QPaintEvent *e);

private slots:
    void on_pushButton_clicked();

    void updateImage(Mat frame);
    void on_pushButton_2_clicked();

    void CreateMutualVideo();

    void CreateAutoVideo();

    void on_checkBox_clicked(bool checked);

    void getParkInfo(int flag, PARKINFO &park);

    void getVideoRecord(int flag);

private:
    Ui::ParkingVCRWin *ui;
    ParkingThread *parkthread;
    Mat frame;
    Mat waterMark;
    Mat Mark;
    ShareInfo *shareinfo;
    QImage q_image; //save image
    QString save_path;
    QString video_path;
    QTimer *Mtimer; //30s mutual
    int stopflag;
    QTimer *Atimer; //30s automatically
    int autoflag;

    //sprintf picture to video
    VideoWriter writer;
    int frame_fps;
    int frame_width;
    int frame_height;
    int frame_num;
    queue<Mat>videoqueue;
    queue<Mat>AutoQueue;
    Mat videoFrame;

    //init some
    PARKINFO parkinfo;
    VIDEOINFO videoinfo;
    HEAD head;
    ReadThread *rt;
    WriteThread *wt;

    QString picture_name;
    QString video_name;
    QString now_time_is;

    char buf[1024];


};

#endif // PARKINGVCRWIN_H
