#include "widget.h"
#include <QApplication>
#include <cmanagewin.h>
#include "mainwindow.h"
#include "csetwin.h"
#include "md5.h"
#include <easypr.h>
#include <QDebug>
#include <cregwin.h>
#include <vector>
#include <QDebug>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <dirent.h>
#include<algorithm>

using namespace std;
using namespace easypr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

//    CManageWin* manager = CManageWin::getInstance();
//    manager->setwin()->show();
//    CSetWin *setwin = new CSetWin();
//    setwin->show();
//    Widget *w = new Widget();
//    w->show();
/*
    CRegWin *reg = new CRegWin();
    reg->show();
*/
    /*
    CEnterWin *enter = new CEnterWin();
    enter->show();
    */


    //real
//    MainWindow *main = new MainWindow();
//    main->show();

    /*
    QString filepath = "./ExportData";
    QString filename= filepath + "/test.csv";
    QFile file(filename);
    //open
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
       qDebug()<<"file open field!" ;
    }
    //write
    QTextStream out(&file);
    out<<"Time,"<<"value,"<<",\n";
    for(int i=0; i<10; i++)
    {
        out<<i<<","<<",\n";
    }
    file.close();
    */
    //QString res = "./TempFile";


    //QString filename = "./CarImage/2022-07-28 00:13:16.png";
    //QString dir = "./TempFile";


    //break;
    //breakpicture(filename,dir);
    //read
    //vector<QString> vct;
    //QString filepath = "./TempFile";
    //sendFile(filepath, vct);
    //sort(vct.begin(), vct.end(),vct_compare);



    /*
    vector<int > test;
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);
    reverse(test.begin(),test.end());
    qDebug()<<test[0];
    */

    return a.exec();

}

/*
    MD5 md;
    String str = md.Encode("hello");
    qDebug()<<str.c_str();
    String str1 = md.Encode("hello");
    qDebug()<<str1.c_str();
*/
