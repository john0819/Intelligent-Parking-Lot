#include "ccaroutwin.h"
#include "ui_ccaroutwin.h"
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>

CCarOutWin::CCarOutWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CCarOutWin)
{
    ui->setupUi(this);
    //share info to this window
    shareinfo = ShareInfo::getInstance();
    //init some
    this->picture_flag=1;
    this->timediff = 0;
    this->money = 0;
    qRegisterMetaType<CAROUT>("CAROUT&");

    this->current_user = shareinfo->getUserNum();
    this->rest_num = shareinfo->getRestNum();
    QString rest = QString::number(shareinfo->getRestNum(),10);
    this->ui->lineEdit_3->setText(rest);
    QString user = QString::number(shareinfo->getUserNum(),10);
    this->ui->lineEdit_4->setText(user);
    this->ui->lineEdit_3->setFocusPolicy(Qt::NoFocus);
    this->ui->lineEdit_4->setFocusPolicy(Qt::NoFocus);
    this->ui->lineEdit_2->setReadOnly(true);

    this->ui->lineEdit_8->setStyleSheet("color:red");
//    this->ui->lineEdit_8->setText("50CNY");
    //change time
    timer = new QTimer(this);
    connect(this->timer,SIGNAL(timeout()),this,SLOT(time_update()));
    timer->start(1000);

    //init some
    this->rt = ReadThread::getInstance();
    this->wt = WriteThread::getInstance();
    memset(&this->head,0,sizeof(this->head));
    memset(&this->carout,0,sizeof(this->carout));

    //start video
    this->leavethread = new CarLeaveThread("./Video/car_input.mp4");
    //this->leavethread = new CarLeaveThread("/root/Qt_Workspace/demo1/Video/carMove.mp4");
    qRegisterMetaType<Mat>("Mat");
    connect(this->leavethread,SIGNAL(frameVideo(Mat)),this,SLOT(getFrame(Mat)),Qt::BlockingQueuedConnection);
    //use monnitor
//    this->leavethread->start();

    //change info
    connect(this,SIGNAL(SendCurrentInfo()),this,SLOT(ChangeCurrentInfo()));

    //get car info
    connect(this->rt, SIGNAL(send2Carout(int, CAROUT&)), this, SLOT(getCaroutInfo(int, CAROUT&)));

    //know whether car go
    connect(this->rt, SIGNAL(send2GoCar(int)), this, SLOT(getCarGo(int)));

    //one picture ok
    this->pt = new PictureThread();
    connect(this->pt, SIGNAL(send2PictureOk(int)), this, SLOT(getPictureOk(int)));

}

CCarOutWin::~CCarOutWin()
{
    delete ui;
}

void CCarOutWin::StartThread()
{
    this->leavethread->start();
}

void CCarOutWin::SaveWaterPicture()
{
    //save plate
    QString save_time = shareinfo->getCurrenttime();
    this->picture_path = save_time;
    //picture name
    QDateTime rest_name = QDateTime::currentDateTime();
    this->picture_name = rest_name.toString("yyyyMMddhhmmss");

    //plate save
    cvtColor(test,test,CV_BGR2RGB);
    this->save_path = "./CarOutPlate/" + save_time + ".jpg";
    //this->q_image.save(this->save_path,"PNG",100);
    imwrite(this->save_path.toStdString().c_str(), this->test);

    //save car
    QString savepath = "./OutImage/" + save_time + ".jpg";
    QString waterpath = "./CarImage/" + save_time + ".png";
    /*
    this->save_path = "./Image/" + shareinfo->getCurrenttime()+ ".png";
    this->q_image.save(this->save_path,"PNG",100);
    */
    Mat waterMark = this->frame.clone();
    cvtColor(waterMark,waterMark,CV_BGR2RGB);
    imwrite(savepath.toStdString().c_str(), waterMark);

    Mat Mark = imread("./Image/logo2.png");
    Mat result;
    cv::resize(Mark, Mark, Size(waterMark.cols, waterMark.rows),0, 0, INTER_CUBIC);
    addWeighted(waterMark,1.0,Mark,0.3,0,result);
    QImage res = QImage(result.data,result.cols,result.rows,QImage::Format_RGB888);
    res.save(waterpath,"PNG",100);

//    this->PlatePicture(this->picture_name);
    //send picture to server
    this->CarPicture(this->picture_name);
}

/*
    calculate the time diff
    parking lot rule:
    >1hour : 5CNY
    per hour: 2CNY
    >1day:

*/
void CCarOutWin::CountTimeDiff(QString s1, QString s2)
{
    //date and time
    QStringList str1 = s1.split(" ");
    QStringList str2 = s2.split(" ");
    QString enter_date = str1[0];
    QString enter_time = str1[1];
    QString out_date = str2[0];
    QString out_time = str2[1];

    QStringList str3 = enter_time.split(":");
    QStringList str4 = out_time.split(":");
    int enter_hour = str3[0].toInt();
    int enter_min = str3[1].toInt();
    int out_hour = str4[0].toInt();
    int out_min = str4[1].toInt();

    int diff = 0;

    if(QString::compare(enter_date, out_date)==0) //same day : diff max  = 1440
    {
        diff = (out_hour*60 + out_min) - (enter_hour*60 +enter_min);
        qDebug()<<diff;
    }
    else //diff day
    {
        QStringList str5 = enter_date.split("-");
        QStringList str6 = out_date.split("-");
        int enter_month = str5[1].toInt();
        int enter_day = str5[2].toInt();
        int out_month = str6[1].toInt();
        int out_day = str6[2].toInt();

        if(enter_month == out_month) //same month
        {
            diff = (out_day *1440 + out_hour*60 + out_min) - (enter_day *1440 + enter_hour*60 + enter_min);
            qDebug()<<diff;
        }
        else if(enter_month != out_month) //diff month : one month (30days)
        {
            out_day = out_day + 30;
            diff = (out_day *1440 + out_hour*60 + out_min) - (enter_day *1440 + enter_hour*60 + enter_min);
            qDebug()<<diff;
        }
    }
    //diff time
    this->timediff = diff;
    QString duration_time = QString::number(diff,10);
    this->ui->lineEdit_7->setText(duration_time);

}

void CCarOutWin::CountMoney(int time)
{
    int judge = time / 1440;
    int money = 5;
    if(judge ==0) //<1day
    {
        int hour = time / 60;
        money = money + hour * 2;
    }
    else //>1day = 50 *per
    {
        money = 50 * judge;
    }
    qDebug()<< money;
    this->money = money;

    //this->ui->lineEdit_8->setText("50CNY");
    QString duration_money = QString::number(this->money,10) + "CNY";
    this->ui->lineEdit_8->setText(duration_money); //set text
}

void CCarOutWin::CarPicture(QString filename)
{
    QString dir = "./TempFile";
    QString filepath = "./CarImage/" + this->picture_path + ".jpg";
    QString realname = filename + "oo";
    this->pt->setDirname(dir);
    this->pt->setFilename(filepath); //path
    this->pt->setPictureName(realname); //name
    this->pt->start(); //send car picture to server

}

void CCarOutWin::PlatePicture(QString filename)
{
    QString dir = "./TempFile2";
    QString filepath = "./CarInPlate/" + this->picture_path + ".jpg";
    QString realname = filename + "po";
    this->pt->setDirname(dir);
    this->pt->setFilename(filepath); //path
    this->pt->setPictureName(realname); //name
    this->pt->start();
}

void CCarOutWin::getPictureOk(int flag)
{
    if(flag ==1) //car picture ok and then start plate picture
    {
        this->pt->quit(); //close thread
        if(this->picture_flag % 2 ==1) //1 3 5
        {
            this->PlatePicture(this->picture_name);
            this->picture_flag++;
        }
    }
}

void CCarOutWin::paintEvent(QPaintEvent *e)
{
    QImage q_image = QImage(frame.data,frame.cols,frame.rows,QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(q_image));
    ui->label->setScaledContents(true);
}

void CCarOutWin::time_update()
{
    this->time = shareinfo->getCurrenttime();
    this->ui->lineEdit_5->setText(this->time);
}

void CCarOutWin::getFrame(Mat frame)
{
    this->frame = frame.clone();
    cvtColor(this->frame,this->frame,CV_BGR2RGB);
    //cvtColor(this->frame,this->frame,CV_BGR2RGB);
}

void CCarOutWin::ChangeCurrentInfo()
{
    //change info
    this->rest_num++;
    this->current_user--;
    //update shareinfo
    this->shareinfo->setRestNum(this->rest_num);
    this->shareinfo->setUserNum(this->current_user);
    QString rest = QString::number(this->rest_num,10);
    QString user = QString::number(this->current_user,10);
    this->ui->lineEdit_3->setText(rest);
    this->ui->lineEdit_4->setText(user);
}

void CCarOutWin::getCaroutInfo(int flag, CAROUT& car)
{
    if(flag == 1)
    {
        memset(&(this->carout),0,sizeof(this->carout));
        //copy all info
        memcpy(this->carout.enter_time, car.enter_time, sizeof(this->carout.enter_time)); //enter time
        memcpy(this->carout.plate,car.plate, sizeof(this->carout.plate));
        memcpy(this->carout.enter_path,car.enter_path, sizeof(this->carout.enter_path));
        memcpy(this->carout.out_path,this->save_path.toStdString().c_str(), sizeof(this->carout.out_path));

        qDebug()<<"this->carout.enter_path = "<<this->carout.enter_path;
        qDebug()<<"this->carout.out_path = "<<this->carout.out_path;

        //calculate time diff
        QString enter_time = this->carout.enter_time;
        //enter time
        this->ui->lineEdit_6->setText(enter_time);

        this->CountTimeDiff(enter_time, Out_time); //this->timediff
        this->CountMoney(this->timediff); //money

        //add new info
        QString duration_time = QString::number(this->timediff,10);
        memcpy(this->carout.duration_time,duration_time.toStdString().c_str(), sizeof(this->carout.duration_time));
        this->carout.charge = this->money;
        this->carout.card =1;
        memcpy(this->carout.out_time,this->Out_time.toStdString().c_str(), sizeof(this->carout.out_time));

    }
    else if (flag == 0) //no plate
    {
        QMessageBox::information(this, "hint", "modify the plate");
    }

}

void CCarOutWin::getCarGo(int flag)
{
    if(flag ==1)
    {
        QMessageBox::information(this, "hint", "user has paid the bill");
    }
    else if(flag ==0)
    {
        QMessageBox::information(this, "hint", "user hasn't paid the bill");
    }
}

//take photo
void CCarOutWin::on_pushButton_2_clicked()
{
    Mat car_number;
       int result = pr.plateRecognize(this->frame,plateVec);
       qDebug()<<"result ="<<result;

       if(result == 0)
       {
           plate = plateVec.at(0); //car info
           plateMat = plate.getPlateMat(); //car number info
           cvtColor(plateMat,car_number,CV_BGR2RGB);
           cvtColor(car_number,car_number,CV_BGR2RGB);
           this->test = car_number;

           this->q_image = QImage(car_number.data,car_number.cols,car_number.rows,QImage::Format_RGB888);
           ui->label_5->setPixmap(QPixmap::fromImage(q_image));
           ui->label_5->setScaledContents(true);

           string str_car_num = plateVec[0].getPlateStr();
           QString q_str = QString::fromLocal8Bit(str_car_num.c_str());
           ui->lineEdit_2->clear();
           ui->lineEdit_2->insert(q_str);

       }

       plateVec.clear();
       //save picture
       this->SaveWaterPicture();
       //set enter parking time
       this->ui->lineEdit->setText(this->time);
       this->Out_time = this->time;

       QString plate_num = this->ui->lineEdit_2->text();
       //send info to server
       memset(&this->carout, 0, sizeof(this->carout));
       memcpy(this->carout.plate, plate_num.toStdString().c_str(), sizeof(this->carout.plate));
       //set head
       char res[1024]={0};
       memcpy(res,&carout,sizeof(this->carout));

       this->head.bussinesstype = 8;
       this->head.CRC = shareinfo->CalcCRCCode((unsigned char*)res, sizeof(this->carout));
       this->head.bussinesslen = sizeof(this->carout);
       //send head + carout
       memset(buf,0,sizeof(this->buf));
       memcpy(buf, &(this->head), sizeof(this->head));
       memcpy(buf+sizeof(this->head), &(this->carout), sizeof(this->carout));
       //set data
       this->wt->setData(this->buf, sizeof(this->head) + sizeof(this->carout));
       qDebug()<<"send server ok and type = 8";
}

//modify
void CCarOutWin::on_pushButton_clicked()
{
    if(this->modify_flag==0)
    {
        this->ui->lineEdit_2->setReadOnly(false);
        this->ui->pushButton->setText("Still");
        this->modify_flag=1;
    }
    else if(this->modify_flag==1)
    {
        this->ui->lineEdit_2->setReadOnly(true);

        //modify ok
        QString plate_num = this->ui->lineEdit_2->text();
        //send info to server
        memset(&this->carout, 0, sizeof(this->carout));
        memcpy(this->carout.plate, plate_num.toStdString().c_str(), sizeof(this->carout.plate));
        //set head
        char res[1024]={0};
        memcpy(res,&this->carout,sizeof(this->carout));

        this->head.bussinesstype = 8;
        this->head.CRC = shareinfo->CalcCRCCode((unsigned char*)res, sizeof(this->carout));
        this->head.bussinesslen = sizeof(this->carout);
        //send head + carout
        memset(buf,0,sizeof(this->buf));
        memcpy(buf, &(this->head), sizeof(this->head));
        memcpy(buf+sizeof(this->head), &(this->carout), sizeof(this->carout));
        //set data
        this->wt->setData(this->buf, sizeof(this->head) + sizeof(this->carout));
        qDebug()<<"modify ok and type = 8";

        this->ui->pushButton->setText("modify");
        this->modify_flag=0;
    }
}

//vip click
void CCarOutWin::on_radioButton_clicked(bool checked)
{
    if(checked == true)
    {
        qDebug()<<"it is vip";
        this->ui->lineEdit_8->setText("0");

        this->carout.charge = 0;
        this->carout.card =0;
    }
}

//user pay the bill and then update the information
void CCarOutWin::on_pushButton_3_clicked()
{
    //change current info
    emit SendCurrentInfo();

    //send info to server
    memset(&this->head, 0 , sizeof(this->head));
    //set head
    char res[1024]={0};
    memcpy(res, &this->carout, sizeof(this->carout));

    this->head.bussinesstype = 9;
    this->head.CRC = shareinfo->CalcCRCCode((unsigned char*)res, sizeof(this->carout));
    this->head.bussinesslen = sizeof(this->carout);
    //send to buf

    memset(buf,0,sizeof(this->buf));
    memcpy(this->buf, &(this->head), sizeof(this->head));
    memcpy(this->buf + sizeof(head), &(this->carout), sizeof(this->carout));
    //set date
    this->wt->setData(this->buf, sizeof(this->head) + sizeof (this->carout));
    qDebug()<<"write ok and type = 9";

    //QMessageBox::information(this, "hint", "user has paid the bill");

}



