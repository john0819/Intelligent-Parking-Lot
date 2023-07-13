#ifndef VCRREVIEWWIN_H
#define VCRREVIEWWIN_H

#include <QListWidgetItem>
#include <QWidget>
#include "bigpicture.h"
#include <QMessageBox>
#include <QPushButton>
#include "cvideoplayer.h"
#include "writethread.h"
#include "readthread.h"
#include "shareinfo.h"

namespace Ui {
class VCRReviewWin;
}

class VCRReviewWin : public QWidget
{
    Q_OBJECT

public:
    explicit VCRReviewWin(QWidget *parent = nullptr);
    ~VCRReviewWin();

private slots:
    void getBigImage(QListWidgetItem *item);
    //void getVideoPlay(QListWidgetItem* item);
    void GetRatio(int ratio);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void getMonthData(int flag, vector<SEARCH> search);

    void getDayData(int flag, vector<SEARCH> search);

    void changeItem(QListWidgetItem *item);

    void getMonthVideo(int flag, vector<VIDEOINFO> video);

    void getDayVideo(int flag, vector<VIDEOINFO> video);

    void getOneVideo(int flag, VIDEOINFO& video);

    void on_pushButton_2_clicked();

    void getMoreMonth(int flag, vector<VIDEOINFO> video);

    void getDayMonth(int flag, vector<VIDEOINFO> video);

private:
    Ui::VCRReviewWin *ui;
    BigPicture *big;
    QPushButton *okbtn;
    QPushButton *nobtn;
    QMessageBox *box;
    QString video_ratio;

    CVideoPlayer *player;

    ReadThread *rt;
    WriteThread *wt;
    HEAD head;
    vector<SEARCH> vec_search;
    SEARCH search;

    VIDEOINFO video;
    vector<VIDEOINFO> vec_video;

    int mORd_flag;

    QString select_date; //+ mORd_flag

    char buf[1024];

    int page;

    int row_in_list2;

    QString select_video;

    QString select_month;

    ShareInfo *shareinfo;
};

#endif // VCRREVIEWWIN_H
