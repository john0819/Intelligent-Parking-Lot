#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cmanagewin.h"
#include "writethread.h"
#include "readthread.h"
#include "shareinfo.h"

#include <QWidget>

class CSetWin;
namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    //explicit MainWindow(QWidget *parent = nullptr);
    static MainWindow *main;
    static MainWindow *getInstence();

    ~MainWindow();

private:
    explicit MainWindow(QWidget *parent = nullptr);
    Ui::MainWindow *ui;
    CManageWin *manager;
    CSetWin *setwin;

    ReadThread *rt;
    WriteThread *wt;
    HEAD head;
    char buf[1024];

    ShareInfo *shareinfo;

public slots:
    void ChangeWidgetSlot();
};

#endif // MAINWINDOW_H
