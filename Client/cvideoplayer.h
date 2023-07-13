#ifndef CVIDEOPLAYER_H
#define CVIDEOPLAYER_H

#include <QWidget>
#include <opencv2/opencv.hpp>
#include "videothread.h"
#include <QMetaType>
#include <QCloseEvent>

using namespace cv;

namespace Ui {
class CVideoPlayer;
}

class CVideoPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit CVideoPlayer(QWidget *parent = nullptr);

    //video name and start
    void setVideoPath(QString filename);
    void StartThread();

    ~CVideoPlayer();

    void setValue(int value);

protected:
     void closeEvent(QCloseEvent *event);

private slots:
    void on_pushButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void getFrame(Mat frame, int num);

    void getCount(double count);



private:
    Ui::CVideoPlayer *ui;
    VideoThread *vthread;
    int count;
    QString process_num;
    int flag;
    int frame_num;
    QString ratio;

signals:
    void changeFlag();
    void sendValue(int value);
    void sendRatio(int str);
};

#endif // CVIDEOPLAYER_H
