#ifndef SHAREINFO_H
#define SHAREINFO_H

#include <QString>

//share information to all window
class ShareInfo
{
public:
    static ShareInfo* getInstance();
    static ShareInfo *shareinfo;

    static void setRestNum(int restnum);
    static void setUserNum(int usernum);
    static void setCurrentTime(QString currenttime);
    static void setUserName(QString username);
    static void setUserId(QString id);

    static void setIp(QString ip);
    static void setHost(QString host);
    static void setPicture(QString Picture);
    static void setVideo(QString Video);
    static void setSize(QString size);


    static int getRestNum();
    static int getUserNum();
    static QString getCurrenttime();
    static QString getUserName();
    static QString getUserId();

    static QString getIp();
    static QString getHost();
    static QString getPicture();
    static QString getVideo();
    static QString getSize();

    static unsigned int CalcCRCCode(unsigned char* Array, unsigned int Len); //CRC

private:
    ShareInfo();
    static int parking_rest_num;
    static int parking_current_user;
    static QString current_time;
    static QString user_name;
    static QString user_id;

    static QString Ip_address;
    static QString Host_address;
    static QString Picture_address;
    static QString Video_address;
    static QString Max_size;

};

#endif // SHAREINFO_H
