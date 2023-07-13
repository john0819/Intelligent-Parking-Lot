#ifndef CCARINWIN_H
#define CCARINWIN_H

#include <QWidget>
#include <QDateTime>
#include <QTimer>
#include "carenterthread.h"
#include <QDebug>
#include <easypr.h>
#include <opencv2/opencv.hpp>
#include "shareinfo.h"
#include "readthread.h"
#include "writethread.h"
#include "picturethread.h"

using namespace easypr;
using namespace cv;

namespace Ui {
class CCarInWin;
}

class CCarInWin : public QWidget
{
    Q_OBJECT

public:
    explicit CCarInWin(QWidget *parent = nullptr);
    static QString getCurrentTime();
    static int Packingrest();
    static int CurrentUser();

    void SaveWaterPicture();

    void CarPicture(QString filename);
    void PlatePicture(QString filename);

    ~CCarInWin();

private:
    Ui::CCarInWin *ui;
    QDateTime systemtime; //show time
    QTimer *timer; //system time
    static QString time;
    int parking_max_num;
    int parking_current_num;
    static int parking_rest_num;
    static int current_user;
    CarEnterThread *carthread;
    Mat frame;
    CPlateRecognize pr;
    VideoCapture cap;
    vector<CPlate> plateVec;
    CPlate plate;
    Mat plateMat;
    int modify_flag;
    ShareInfo *shareinfo;
    QImage q_image;
    //modify plate
    QString firstplate;
    QString secondplate;

    //thread
    ReadThread *rt;
    WriteThread *wt;
    UPDATE updatecar;
    HEAD head;
    char buf[1024];

    CARIN car;
    vector<CARIN> carin;
    vector<CARIN> morecar; //add more 4 cars
    REGISTER reg;
    LOAD load;
    QString save_path; //image path
    int page; //page number

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
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void updateImage(Mat frame);
    void ChangeCurrentInfo();

    void doubleClickInfo(int row, int col);
    void updateTable(REGISTER &reg, vector<CARIN> car);
    void ChangeTable(vector<CARIN> car);
    void oneDetailCar(CARIN& car);
    void getMoreCar(int flag, vector<CARIN> car);

    void on_pushButton_3_clicked();

    void getPictureOk(int flag);

    void get2PictureSave(int flag);

signals:
    void SendCurrentInfo();
};

#endif // CCARINWIN_H
