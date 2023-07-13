#include "shareinfo.h"

ShareInfo* ShareInfo::shareinfo=nullptr;
int ShareInfo::parking_rest_num=0;
int ShareInfo::parking_current_user=0;
QString ShareInfo::current_time;
QString ShareInfo::user_name;
QString ShareInfo::user_id;

QString ShareInfo::Ip_address;
QString ShareInfo::Host_address;
QString ShareInfo::Picture_address;
QString ShareInfo::Video_address;
QString ShareInfo::Max_size;

ShareInfo *ShareInfo::getInstance()
{
    if(ShareInfo::shareinfo == nullptr)
    {
        ShareInfo::shareinfo = new ShareInfo();
    }
    return ShareInfo::shareinfo;
}

void ShareInfo::setRestNum(int restnum)
{
    ShareInfo::parking_rest_num = restnum;
}

void ShareInfo::setUserNum(int usernum)
{
    ShareInfo::parking_current_user = usernum;
}

void ShareInfo::setCurrentTime(QString currenttime)
{
    ShareInfo::current_time = currenttime;
}

void ShareInfo::setUserName(QString username)
{
    ShareInfo::user_name = username;
}

void ShareInfo::setUserId(QString id)
{
    ShareInfo::user_id = id;
}

void ShareInfo::setIp(QString ip)
{
    ShareInfo::Ip_address = ip;
}

void ShareInfo::setHost(QString host)
{
    ShareInfo::Host_address = host;
}

void ShareInfo::setPicture(QString Picture)
{
    ShareInfo::Picture_address = Picture;
}

void ShareInfo::setVideo(QString Video)
{
    ShareInfo::Video_address = Video;
}

void ShareInfo::setSize(QString size)
{
    ShareInfo::Max_size = size;
}

int ShareInfo::getRestNum()
{
    return ShareInfo::parking_rest_num;
}

int ShareInfo::getUserNum()
{
    return ShareInfo::parking_current_user;
}

QString ShareInfo::getCurrenttime()
{
    return ShareInfo::current_time;
}

QString ShareInfo::getUserName()
{
    return ShareInfo::user_name;
}

QString ShareInfo::getUserId()
{
    return ShareInfo::user_id;
}

QString ShareInfo::getIp()
{
    return ShareInfo::Ip_address;
}

QString ShareInfo::getHost()
{
    return ShareInfo::Host_address;
}

QString ShareInfo::getPicture()
{
    return ShareInfo::Picture_address;
}

QString ShareInfo::getVideo()
{
    return ShareInfo::Video_address;
}

QString ShareInfo::getSize()
{
    return ShareInfo::Max_size;
}

//==================================================
//函数名称：uByte CalcCRCCode（uByte *Array， uByte Len）
//输入参数：需要计算 CRC 的数据首地址、数据个数
//输出参数：对应数据的 CRC 校验码
//函数功能：计算数据的 CRC 校验码
//==================================================
unsigned int ShareInfo::CalcCRCCode(unsigned char *Array, unsigned int Len)
{

    unsigned int i = 0;
        unsigned int j = 0;
        const unsigned short CalcConst = 0xFFFF;
        unsigned int TempOut = 0;
        for (i = 0; i < Len; i++)
        {
            TempOut = CalcConst ^ Array[i];
            for (j = 0; j < 8; j++)
            {
                if (TempOut & 0x0001)
                {
                    TempOut = TempOut >> 1;
                    TempOut ^= 0xA001;
                }
                else {
                    TempOut = TempOut >> 1;
                }
            }
        }
        return(TempOut);
}

ShareInfo::ShareInfo()
{

}
