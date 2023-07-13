#ifndef CCAROUTWIN_H
#define CCAROUTWIN_H

#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <easypr.h>
#include <opencv2/opencv.hpp>
#include "shareinfo.h"
#include "carleavethread.h"
#include "readthread.h"
#include "writethread.h"
#include "picturethread.h"
#include "shareinfo.h"

using namespace easypr;
using namespace cv;

namespace Ui {
class CCarOutWin;
}

class CCarOutWin : public QWidget
{
    Q_OBJECT

public:
    explicit CCarOutWin(QWidget *parent = nullptr);
    ~CCarOutWin();
    void StartThread();
    void SaveWaterPicture();
    void CountTimeDiff(QString s1, QString s2); //time
    void CountMoney(int time); //money for time

    void CarPicture(QString filename);
    void PlatePicture(QString filename);


private:
    Ui::CCarOutWin *ui;
    ShareInfo *shareinfo;
    QTimer *timer;
    Mat frame;
    CarLeaveThread *leavethread;
    QString time;
    int rest_num;
    int current_user;

    CPlateRecognize pr;
    VideoCapture cap;
    vector<CPlate> plateVec;
    CPlate plate;
    Mat plateMat;
    int modify_flag;
    QImage q_image;

    QString save_path;

    int timediff;
    int money;

    //init some
    ReadThread *rt;
    WriteThread *wt;
    HEAD head;
    CAROUT carout;
    char buf[1024];
    QString Out_time;

    int picture_flag;
    QString picture_name;
    QString picture_path;

    //picture thread
    PictureThread *pt;


    Mat test;

protected:
    void paintEvent(QPaintEvent *e);

public slots:
    void time_update(void);
    void getFrame(Mat frame);
    void ChangeCurrentInfo();
    void getCaroutInfo(int flag, CAROUT& car);
    void getCarGo(int flag);
    void getPictureOk(int flag);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_radioButton_clicked(bool checked);

    void on_pushButton_3_clicked();

signals:
    void SendCurrentInfo();
};

#endif // CCAROUTWIN_H
