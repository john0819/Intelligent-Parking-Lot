#ifndef CENTERWIN_H
#define CENTERWIN_H

#include <QWidget>
#include "verificationcodelabel.h"
#include "readthread.h"
#include "writethread.h"
#include <mainwindow.h>
#include "cregwin.h"
#include "md5.h"
#include "shareinfo.h"

namespace Ui {
class CEnterWin;
}

class CEnterWin : public QWidget
{
    Q_OBJECT

public:
    explicit CEnterWin(QWidget *parent = nullptr);
    ~CEnterWin();

private slots:
    void on_pushButton_clicked();

    void isCheck(int flag);

    void on_pushButton_2_clicked();

private:
    Ui::CEnterWin *ui;
    ReadThread *rt;
    WriteThread *wt;

    HEAD head;
    FEEDBACK feed;
    LOGIN login;

    char buf[1024];

    MainWindow *mainwin;
    CRegWin *regwin;

    ShareInfo *shareinfo;
};

#endif // CENTERWIN_H
