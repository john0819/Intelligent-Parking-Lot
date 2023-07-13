#ifndef READTHREAD_H
#define READTHREAD_H

#include "protocol.h"
#include <QDebug>
#include "QThread"
#include <vector>

using namespace std;

// readthread used for get information from server
class ReadThread : public QThread
{
    Q_OBJECT
public:
    static ReadThread * readthread;
    static ReadThread * getInstance();

    void run();
    void * getUserid();
    void setSocketfd(int value); // socketfd from server
private:
    ReadThread();

    int socketfd;
    HEAD data;
    FEEDBACK feek;
    REGISTER regist;
    LOGIN login;
    CARIN car;
    CAROUT carout;
    PARKINFO parkinfo;
    SEARCH search;
    VIDEOINFO video;
    CINFO cinfo;

    vector<CARIN> carin; //save info
    vector<SEARCH> vec_search;
    vector<VIDEOINFO> vec_video;
    vector<CINFO> vec_info;
    char buf[1024];

    char userid[20];

signals:
    void send2RigWidget(int flag);
    void send2Enter(int flag);
    void send2Carin(REGISTER &reg, vector<CARIN> car);
    void send2Table(vector<CARIN> car);
    void send2Carout(int flag, CAROUT &carout);
    void send2OneCar(CARIN &car);
    void send2MoreCarin(int flag, vector<CARIN> car);
    void send2GoCar(int flag);
    void send2ParkInfo(int flag, PARKINFO &);
    void send2Video(int flag);
    void send2MonthSearch(int flag, vector<SEARCH> search);
    void send2DaySearch(int flag, vector<SEARCH> search);
    void send2MonthData(int flag, vector<VIDEOINFO> video);
    void send2DayData(int flag, vector<VIDEOINFO> video);
    void send2OneVideo(int flag, VIDEOINFO& video);
    void send2MoreMonth(int flag, vector<VIDEOINFO> video);
    void send2MoreDay(int flag, vector<VIDEOINFO> video);
    void send2SearchData(int flag, vector<CINFO> info);
    void send2SearchMore(int flag, vector<CINFO> info);
    void send2PictureSave(int flag);
};

#endif // READTHREAD_H
