#include "readthread.h"
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

ReadThread * ReadThread::readthread =nullptr;

ReadThread *ReadThread::getInstance()
{
    if(ReadThread::readthread == nullptr)
    {
        ReadThread::readthread = new ReadThread();
    }
    return ReadThread::readthread;
}

void ReadThread::run()
{
    while(1)
    {
        int res = read(this->socketfd, &(this->feek), sizeof(FEEDBACK));
        //judge the information from which window
        if(feek.bussinesstype==1) //signWin
        {
            if(feek.flag==1)
            {
                emit send2RigWidget(1);
            }
            else if(feek.flag==0)
            {
                qDebug()<<"enter system error ....";
                emit send2RigWidget(0);
            }
        }
        else if(feek.bussinesstype==2) //head + reg + carin + ... + carin
        {
            if(feek.flag==1)
            {
                emit send2Enter(1); //send to EnterWin (judge successful login)
                qDebug()<<"enter system ok";

                memset(&this->regist,0,sizeof(this->regist));
                carin.clear();
                res = read(this->socketfd,&(this->regist),sizeof(REGISTER));
                int length = feek.bussinesslen - sizeof(REGISTER); //the length of carin
                int number = length / sizeof(CARIN); //the number of cain
                qDebug()<<number;
                for(int i=0; i<number; i++)
                {
                    memset(&this->car,0,sizeof(this->car));
                    res = read(this->socketfd, &(this->car),sizeof(CARIN));
                    carin.push_back(this->car);
                }
                for(int i=0; i <number; i++)
                {
                    qDebug()<<carin[i].imageid;
                    qDebug()<<carin[i].plate;
                    qDebug()<<carin[i].site;
                    qDebug()<<carin[i].time;
                }

                qDebug()<<"write vector<CARIN> ok";
                //reverse(this->carin.begin(),this->carin.end());

                emit send2Carin(this->regist, this->carin);
                qDebug()<<"send info to CarinWin ok";
                //emit send2UI(&(this->chatmsg));
            }
            else if(feek.flag==0)
            {
                emit send2Enter(0);
                qDebug()<<"send message error";
            }
        }
        else if(feek.bussinesstype ==3) //enter Carin Window
        {
            if(feek.flag ==1)
            {
                carin.clear();
                int number = feek.bussinesslen / sizeof(CARIN);
                for(int i=0; i<number; i++)
                {
                    memset(&this->car,0,sizeof(this->car));
                    res = read(this->socketfd, &(this->car),sizeof(CARIN));
                    carin.push_back(this->car);
                }
                qDebug()<<"write vector<CARIN> ok";
                //reverse(this->carin.begin(),this->carin.end());
                emit send2Table(carin);
                qDebug()<<"send table to CarinWin ok, type =3";

            }
            else if(feek.flag ==0)
            {

                qDebug()<<"send image error";
            }
        }
        else if(feek.bussinesstype ==4) //add new car
        {
            if(feek.flag ==1)
            {
                carin.clear();
                int number = feek.bussinesslen / sizeof(CARIN);
                for(int i=0; i<number; i++)
                {
                    memset(&this->car,0,sizeof(this->car));
                    res = read(this->socketfd, &(this->car),sizeof(CARIN));
                    carin.push_back(this->car);
                }
                qDebug()<<"write vector<CARIN> ok";
                //reverse(this->carin.begin(),this->carin.end());
                emit send2Table(carin);
                qDebug()<<"send table to CarinWin ok";

            }
            else if(feek.flag == 0 )
            {
                qDebug()<<"add new car error, type =4";
            }
        }
        else if(feek.bussinesstype ==5)
        {
            if(feek.flag ==1)
            {
                carin.clear();
                int number = feek.bussinesslen / sizeof(CARIN);
                for(int i=0; i<number; i++)
                {
                    memset(&this->car,0,sizeof(this->car));
                    res = read(this->socketfd, &(this->car),sizeof(CARIN));
                    carin.push_back(this->car);
                }
                qDebug()<<"write vector<CARIN> ok";
                //reverse(this->carin.begin(),this->carin.end());
                emit send2Table(carin);
                qDebug()<<"send table to CarinWin ok";

            }
            else if(feek.flag ==0)
            {
                qDebug()<<"modify old car error, type =5";
            }
        }
        else if(feek.bussinesstype ==6)
        {
            if(feek.flag ==1)
            {
                carin.clear();
                int number = feek.bussinesslen / sizeof(CARIN);
                for(int i=0; i<number; i++)
                {
                    memset(&this->car,0,sizeof(this->car));
                    res = read(this->socketfd, &(this->car),sizeof(CARIN));
                    carin.push_back(this->car);
                }
                qDebug()<<"write vector<CARIN> ok";
                //reverse(this->carin.begin(),this->carin.end());
                emit send2MoreCarin(1, carin);
                qDebug()<<"send more car to CarinWin ok";

            }
            else if(feek.flag==0)
            {
                carin.clear();
                emit send2MoreCarin(0, carin);
            }
        }
        else if(feek.bussinesstype ==7)
        {
            if(feek.flag ==1)
            {
                memset(&this->car,0,sizeof(this->car));
                res = read(this->socketfd, &(this->car), sizeof(this->car));
                emit send2OneCar(this->car);
                qDebug()<<"send one car to CarinWin ok, type =7";
            }
            else if(feek.flag ==0)
            {
                qDebug()<<"one car detail info x, type =7";
            }
        }
        else if(feek.bussinesstype ==8) //carout
        {
            if(feek.flag ==1)
            {
                memset(&this->carout,0,sizeof(this->carout));
                res = read(this->socketfd, &(this->carout), feek.bussinesslen);
                qDebug()<<"this->carout.enter_path = "<<this->carout.enter_path;

                emit send2Carout(1 ,this->carout);
            }
            else if(feek.flag ==0)
            {
                memset(&this->carout,0,sizeof(this->carout));
                emit send2Carout(0, this->carout);
            }
        }
        else if(feek.bussinesstype ==9)
        {
            if(feek.flag ==1)
            {
                emit send2GoCar(1);
                qDebug()<<"car go ok, type =9";
            }
            else if(feek.flag ==0)
            {
                emit send2GoCar(0);
                qDebug()<<"car go not, type =9";
            }
        }
        else if(feek.bussinesstype ==10) //parkinfo
        {
            if(feek.flag ==1)
            {
                memset(&this->parkinfo, 0, sizeof(this->parkinfo));
                res = read(this->socketfd, &(this->parkinfo), sizeof(PARKINFO));
                emit send2ParkInfo(1, this->parkinfo);
                qDebug()<<"park info send, type = 10";
            }
            else if(feek.flag ==0)
            {
                memset(&this->parkinfo, 0, sizeof(this->parkinfo));
                emit send2ParkInfo(0, this->parkinfo);
                qDebug()<<"no park info";
            }
        }
        else if(feek.bussinesstype ==11)
        {
            if(feek.flag ==1)
            {
                send2Video(1);
                qDebug()<<"video ok, type =11";
            }
            else if(feek.flag ==0)
            {
                send2Video(0);
                qDebug()<<"video no, type =11";
            }
        }
        else if(feek.bussinesstype ==12) //month
        {
            if(feek.flag ==1)
            {
                qDebug()<<"feek.bussinesslen = "<<feek.bussinesslen;

                this->vec_search.clear();
                int number = feek.bussinesslen / sizeof(SEARCH);
                for(int i=0; i<number; i++)
                {
                    memset(&this->search,0,sizeof(this->search));
                    res = read(this->socketfd, &(this->search),sizeof(SEARCH));
                    qDebug()<<"this->search.month = "<<this->search.month;
                    this->vec_search.push_back(this->search);
                }
                qDebug()<<"write vector<SEARCH> ok";
                emit send2MonthSearch(1, this->vec_search);
                qDebug()<<"send info to search, type ==12";

            }
            else if(feek.flag ==0)
            {
                this->vec_search.clear();
                emit send2MonthSearch(0, this->vec_search);
                qDebug()<<"no !! send info to search, type ==12";
            }
        }
        else if(feek.bussinesstype ==13) //day
        {
            if(feek.flag ==1)
            {
                qDebug()<<"feek.bussinesslen"<<feek.bussinesslen;
                //send2DaySearch
                this->vec_search.clear();
                int number = feek.bussinesslen / sizeof(SEARCH);
                for(int i=0; i<number; i++)
                {
                    memset(&this->search,0,sizeof(this->search));
                    res = read(this->socketfd, &(this->search),sizeof(SEARCH));
                    qDebug()<<"this->search.date = "<<this->search.date;

                    this->vec_search.push_back(this->search);
                }
                qDebug()<<"write vector<SEARCH> ok";
                emit send2DaySearch(1, this->vec_search);
                qDebug()<<"send info to search, type ==13";
            }
            else if(feek.flag ==0)
            {
                this->vec_search.clear();
                emit send2DaySearch(0, this->vec_search);
                qDebug()<<"no !! send info to search, type ==13";
            }
        }
        else if(feek.bussinesstype ==14) //month
        {
            if(feek.flag ==1)
            {
                qDebug()<<"feek.bussinesslen = "<<feek.bussinesslen;

                this->vec_video.clear();
                int number = feek.bussinesslen /sizeof(VIDEOINFO);
                for(int i=0;i<number;i++)
                {
                    memset(&(this->video),0,sizeof(this->video));
                    res = read(this->socketfd,&(this->video),sizeof(VIDEOINFO));
                    qDebug()<<"this->video.videoname ="<< this->video.videoname;
                    qDebug()<<"this->video ="<< this->video.month;
                    this->vec_video.push_back(this->video);
                }
                qDebug()<<"write vector<VIDEOINFO> ok";
                emit send2MonthData(1, this->vec_video);
                qDebug()<<"send info to data, type ==14";

            }
            else if(feek.flag ==0)
            {
                this->vec_video.clear();
                emit send2MonthData(0, this->vec_video);
                qDebug()<<"no send info to data, type ==14";

            }
        }
        else if(feek.bussinesstype ==15) //day
        {
            if(feek.flag ==1)
            {
                this->vec_video.clear();
                int number = feek.bussinesslen /sizeof(VIDEOINFO);
                for(int i=0;i<number;i++)
                {
                    memset(&(this->video),0,sizeof(this->video));
                    res = read(this->socketfd,&(this->video),sizeof(VIDEOINFO));
                    this->vec_video.push_back(this->video);
                }
                qDebug()<<"write vector<VIDEOINFO> ok";
                emit send2DayData(1, this->vec_video);
                qDebug()<<"send info to data, type ==15";

            }
            else if(feek.flag ==0)
            {
                this->vec_video.clear();
                emit send2DayData(0, this->vec_video);
                qDebug()<<" no send info to data, type ==15";
            }
        }
        else if(feek.bussinesstype ==16) //get video
        {
            if(feek.flag==1)
            {
                qDebug()<<"feek.bussinesslen = "<<feek.bussinesslen;
                memset(&(this->video),0,sizeof(this->video));
                res = read(this->socketfd,&(this->video),sizeof(VIDEOINFO));
                qDebug()<<"video.video_path = "<<video.video_path;
                qDebug()<<"video.video_num = "<<video.video_num;
                qDebug()<<"video.video_count = "<<video.video_count;
                emit send2OneVideo(1,this->video);
            }
            else if(feek.flag ==0)
            {
                memset(&(this->video),0,sizeof(this->video));
                emit send2OneVideo(0,this->video);
            }
        }
        else if(feek.bussinesstype ==17)
        {
            if(feek.flag ==1)
            {
                this->vec_video.clear();
                int number = feek.bussinesslen /sizeof(VIDEOINFO);
                for(int i=0;i<number;i++)
                {
                    memset(&(this->video),0,sizeof(this->video));
                    res = read(this->socketfd,&(this->video),sizeof(VIDEOINFO));
                    this->vec_video.push_back(this->video);
                }
                qDebug()<<"write vector<VIDEOINFO> ok";
                emit send2MoreMonth(1,this->vec_video);
                qDebug()<<"send more video, type =17";

            }
            else if(feek.flag==0)
            {
                this->vec_video.clear();
                emit send2MoreMonth(0,this->vec_video);
            }
        }
        else if(feek.bussinesstype ==18)
        {
            if(feek.flag ==1)
            {
                this->vec_video.clear();
                int number = feek.bussinesslen /sizeof(VIDEOINFO);
                for(int i=0;i<number;i++)
                {
                    memset(&(this->video),0,sizeof(this->video));
                    res = read(this->socketfd,&(this->video),sizeof(VIDEOINFO));
                    this->vec_video.push_back(this->video);
                }
                qDebug()<<"write vector<VIDEOINFO> ok";
                emit send2MoreDay(1,this->vec_video);
                qDebug()<<"send more video, type =18";
            }
            else if(feek.flag==0)
            {
                this->vec_video.clear();
                emit send2MoreDay(0,this->vec_video);
            }
        }
        else if(feek.bussinesstype ==19)
        {
            if(feek.flag ==1)
            {
                qDebug()<<"save ok, type = 19";
            }
        }
        else if(feek.bussinesstype ==20)
        {
            if(feek.flag ==1)
            {
                qDebug()<<"save ok, type =20";
                //send2PictureSave(1);
            }
            else if(feek.flag ==0)
            {
                qDebug()<<"save bad, type =20";
                emit send2PictureSave(0);
            }
        }
        else if(feek.bussinesstype ==21)
        {
            if(feek.flag ==1)
            {
                qDebug()<<"bussinesslen = "<<feek.bussinesslen;
                qDebug()<<"this is type = 21";
                this->vec_info.clear();
                int number = feek.bussinesslen /sizeof(CINFO);
                for(int i=0;i<number;i++)
                {
                    memset(&(this->cinfo),0,sizeof(this->cinfo));
                    res = read(this->socketfd,&(this->cinfo),sizeof(CINFO));

                    qDebug()<<"this->cinfo.plate = "<<this->cinfo.plate;
                    qDebug()<<"this->cinfo.out_path = "<<this->cinfo.out_path;
                    qDebug()<<"this->cinfo.charge = "<<this->cinfo.charge;
                    qDebug()<<"this->cinfo.in_path"<<this->cinfo.in_path;
                    qDebug()<<"<<<<>>>>>";

                    this->vec_info.push_back(this->cinfo);
                }
                qDebug()<<"write vector<CINFO> ok";
                emit send2SearchData(1,this->vec_info);
                qDebug()<<"send data, type =21";
            }
            else if(feek.flag ==0)
            {
                this->vec_info.clear();
                emit send2SearchData(0,this->vec_info);
                qDebug()<<"no info , type =21";
            }
        }
        else if(feek.bussinesstype ==22)
        {
            if(feek.flag ==1)
            {
                this->vec_info.clear();
                int number = feek.bussinesslen /sizeof(CINFO);
                for(int i=0;i<number;i++)
                {
                    memset(&(this->cinfo),0,sizeof(this->cinfo));
                    res = read(this->socketfd,&(this->cinfo),sizeof(CINFO));
                    this->vec_info.push_back(this->cinfo);
                }
                qDebug()<<"write vector<CINFO> ok";
                emit send2SearchMore(1,this->vec_info);
                qDebug()<<"send data, type =22";
            }
            else if(feek.flag ==0)
            {
                this->vec_info.clear();
                emit send2SearchMore(0,this->vec_info);

            }
        }

        bzero(&(this->feek),sizeof(this->feek));

    }
}

void *ReadThread::getUserid()
{

}

void ReadThread::setSocketfd(int value)
{
    this->socketfd = value;
}

ReadThread::ReadThread()
{
    carin.clear();
    bzero(&(this->car),sizeof(this->car));
    bzero(&(this->feek),sizeof(this->feek));
    bzero(&(this->login),sizeof(this->login));
    bzero(&(this->regist),sizeof(this->regist));
    bzero(&(this->carout),sizeof(this->carout));
    bzero(userid,sizeof(userid));
}
