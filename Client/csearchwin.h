#ifndef CSEARCHWIN_H
#define CSEARCHWIN_H

#include <QWidget>
#include <QCalendarWidget>
#include "readthread.h"
#include "writethread.h"
#include <vector>
#include "shareinfo.h"

using namespace std;

namespace Ui {
class CSearchWin;
}

class CSearchWin : public QWidget
{
    Q_OBJECT

public:
    explicit CSearchWin(QWidget *parent = nullptr);
    ~CSearchWin();

private:
    Ui::CSearchWin *ui;
    QCalendarWidget *calendar;
    QCalendarWidget *calendar1;

    //init some
    ReadThread *rt;
    WriteThread *wt;
    HEAD head;
    CAROUT *carout;
    char buf[1024];
    int page;

    vector<CAROUT> vec_car;
    vector<CINFO> vec_info;

    CSEARCH csearch;

    ShareInfo *shareinfo;

public slots:
    void getClicked();
    void getClicked1();
    void selectDate(const QDate &data);
    void selectDate1(const QDate &data);

    void getDataInfo(int flag, vector<CINFO> info);
    void getMoreInfo(int flag, vector<CINFO> info);
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();
};

#endif // CSEARCHWIN_H
