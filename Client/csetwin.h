#ifndef CSETWIN_H
#define CSETWIN_H

#include <QWidget>
#include <vector>
#include "shareinfo.h"

#include "readthread.h"
#include "writethread.h"
#include "socketconnect.h"
#include "centerwin.h"

using namespace std;


namespace Ui {
class CSetWin;
}

class CSetWin : public QWidget
{
    Q_OBJECT

public:
    explicit CSetWin(QWidget *parent = nullptr);
    static QString getPicturePath();
    static QString getVideoPath();
    void JudgeFirst();
    void Send2Share();

    ~CSetWin();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::CSetWin *ui;
    static QString PicturePath;
    static QString VideoPath;
    vector<QString> info; //save all info
    ShareInfo *shareinfo;

    SocketConnect *sc;
    ReadThread *rt;
    WriteThread *wt;

    CEnterWin *enterWin; //next window
};

#endif // CSETWIN_H
