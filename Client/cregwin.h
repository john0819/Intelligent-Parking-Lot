#ifndef CREGWIN_H
#define CREGWIN_H

#include <QWidget>
#include "readthread.h"
#include "writethread.h"
#include "md5.h"
#include "shareinfo.h"

class CEnterWin;
namespace Ui {
class CRegWin;
}

class CRegWin : public QWidget
{
    Q_OBJECT

public:
    explicit CRegWin(QWidget *parent = nullptr);
    ~CRegWin();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void isChecked(int flag);

private:
    Ui::CRegWin *ui;
    int flag;
    CEnterWin *enter;
    ReadThread *rt;
    WriteThread *wt;

    HEAD head;
    FEEDBACK feed;
    Register reg;

    ShareInfo *shareinfo;

    char buf[1024];
};

#endif // CREGWIN_H
