#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include "mythread.h"
#include "csetwin.h"

using namespace cv;


namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    Mat frame;
    MyThread *mythread;
    CSetWin *setwin;


public slots:
    void GetFrame(Mat frame);
    void changeWin();
};

#endif // WIDGET_H
