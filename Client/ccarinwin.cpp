#include "ccarinwin.h"
#include "ui_ccarinwin.h"
#include <QMessageBox>
#include <string.h>
#include <stdlib.h>
#include "onecarwin.h"

QString CCarInWin::time;
int CCarInWin::current_user=0;
int CCarInWin::parking_rest_num=0;

CCarInWin::CCarInWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CCarInWin)
{
    ui->setupUi(this);
    //storage all information
    this->shareinfo = ShareInfo::getInstance();

    //init some
    this->picture_flag=1;
    this->parking_max_num=1000;
    this->parking_current_num=0;
    this->page = 0;
    CCarInWin::parking_rest_num=this->parking_max_num-this->parking_current_num;
    shareinfo->setRestNum(CCarInWin::parking_rest_num);
    CCarInWin::current_user=0;
    shareinfo->setUserNum(CCarInWin::current_user);
    this->modify_flag=0;
    this->carthread = new CarEnterThread("./Video/car_input.mp4");
    qRegisterMetaType<Mat>("Mat");
    qRegisterMetaType<vector<CARIN>>("vector<CARIN>");
    qRegisterMetaType<REGISTER>("REGISTER&");
    qRegisterMetaType<CARIN>("CARIN&");
    //change int to qstring
    QString restnum = QString::number((this->parking_max_num-this->parking_current_num),10);
    this->ui->lineEdit_3->setText(restnum);
//    QString user = QString::number(CCarInWin::current_user,10);
//    this->ui->lineEdit_4->setText(user);
    //limit edit cannt press
    this->ui->lineEdit->setFocusPolicy(Qt::NoFocus);
    this->ui->lineEdit_2->setReadOnly(true);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //init thread and clear some
    this->rt = ReadThread::getInstance();
    this->wt = WriteThread::getInstance();
    memset(&this->updatecar, 0, sizeof(this->updatecar));
    memset(&this->head, 0 ,sizeof(this->head));
    memset(&this->car,0, sizeof(this->car));
    memset(&this->reg,0, sizeof(this->reg));
    memset(&this->load,0,sizeof(this->load));
    carin.clear();
    morecar.clear();

    //set the count of rows and columns
    this->ui->tableWidget->setColumnCount(4);
//    this->ui->tableWidget->setRowCount(4);
    this->ui->tableWidget->verticalHeader()->setHidden(true);  //hide some
    //fill in the table
    this->ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //update the system 1s
    timer = new QTimer(this);
    connect(this->timer,SIGNAL(timeout()),this,SLOT(time_update()));
    timer->start(1000);
    //start car input
    connect(this->carthread,SIGNAL(frameVideo(Mat)),this,SLOT(updateImage(Mat)),Qt::BlockingQueuedConnection);
    this->carthread->start();
    //change current info
    connect(this,SIGNAL(SendCurrentInfo()),this,SLOT(ChangeCurrentInfo()));

    //change table and info :first
    connect(this->rt, SIGNAL(send2Carin(REGISTER& ,vector<CARIN>)),this, SLOT(updateTable(REGISTER& ,vector<CARIN>)));
    //add and modify
    connect(this->rt,SIGNAL(send2Table(vector<CARIN>)),this,SLOT(ChangeTable(vector<CARIN>)));
    //get car info
    connect(this->ui->tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(doubleClickInfo(int, int)));
    //get one car window
    connect(this->rt, SIGNAL(send2OneCar(CARIN&)), this, SLOT(oneDetailCar(CARIN&)));

    //get more car
    connect(this->rt,SIGNAL(send2MoreCarin(int,vector<CARIN>)),this,SLOT(getMoreCar(int, vector<CARIN>)));

    //save picture
    connect(this->rt,SIGNAL(send2PictureSave(int)),this, SLOT(get2PictureSave(int)));

    //one picture ok
    this->pt = new PictureThread();
    connect(this->pt, SIGNAL(send2PictureOk(int)), this, SLOT(getPictureOk(int)));



    //qDebug()<<this->ui->tableWidget->rowCount();
    //test
    this->ui->tableWidget->verticalScrollBar();

}

//get some info
QString CCarInWin::getCurrentTime()
{
    return CCarInWin::time;
}

int CCarInWin::Packingrest()
{
    return CCarInWin::parking_rest_num;
}

int CCarInWin::CurrentUser()
{
    return CCarInWin::parking_rest_num;
}

//save car picture and water frame
void CCarInWin::SaveWaterPicture()
{
    QString save_time = shareinfo->getCurrenttime();
    this->picture_path = save_time;
    //picture name
    QDateTime rest_name = QDateTime::currentDateTime();
    this->picture_name = rest_name.toString("yyyyMMddhhmmss");

    cvtColor(test,test,CV_BGR2RGB);
    //plate save
    this->save_path = "./CarInPlate/" + save_time + ".jpg";
//    this->q_image.save(this->save_path,"PNG",100); //this->test
    imwrite(this->save_path.toStdString().c_str(), this->test);

    //car picture save
    QString savepath = "./CarImage/" + save_time + ".jpg";
    QString waterpath = "./CarImage/" + save_time + ".png";
    /*
    this->save_path = "./Image/" + shareinfo->getCurrenttime()+ ".png";
    this->q_image.save(this->save_path,"PNG",100);
    */
    Mat waterMark = this->frame.clone();
    cvtColor(waterMark,waterMark,CV_BGR2RGB);
    //server save
    imwrite(savepath.toStdString().c_str(), waterMark);
    //Local save
    Mat Mark = imread("./Image/logo2.png");
    Mat result;
    cv::resize(Mark, Mark, Size(this->frame.cols, this->frame.rows),0, 0, INTER_CUBIC);
    addWeighted(this->frame,1.0,Mark,0.3,0,result);
    QImage res = QImage(result.data,result.cols,result.rows,QImage::Format_RGB888);
    res.save(waterpath,"PNG",100);

    //send picture to server
    this->CarPicture(this->picture_name);
//    this->PlatePicture(this->picture_name);
}

CCarInWin::~CCarInWin()
{
    delete ui;
}

void CCarInWin::paintEvent(QPaintEvent *e)
{
    QImage q_image = QImage(frame.data,frame.cols,frame.rows,QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(q_image));
    ui->label->setScaledContents(true);
}

//update the system time
void CCarInWin::time_update()
{
    this->systemtime = QDateTime::currentDateTime();
    CCarInWin::time = this->systemtime.toString("yyyy-MM-dd hh:mm:ss");
    this->shareinfo->setCurrentTime(CCarInWin::time);
    this->ui->lineEdit_5->setText(CCarInWin::time);
}

//modify the car licence plate number
void CCarInWin::on_pushButton_clicked()
{
    //click modify -> change plate and then click still means that change ok
    if(this->modify_flag==0) //modify the picture and update the table + sqlite3
    {
        this->ui->lineEdit_2->setReadOnly(false);
        this->ui->pushButton->setText("Still");
        this->modify_flag=1;
    }
    else if(this->modify_flag==1) //update
    {
        //change plate -> to server
        this->secondplate = ui->lineEdit_2->text();
        qDebug()<<"second = "<<this->secondplate;

        memcpy(this->updatecar.first,this->firstplate.toStdString().c_str(),sizeof(this->updatecar.first));
        memcpy(this->updatecar.second,this->secondplate.toStdString().c_str(),sizeof(this->updatecar.second));
        qDebug()<<"this->update->first"<<this->updatecar.first;
        qDebug()<<"this->update->second"<<this->updatecar.second;
        //set head
        char res[1024]={0};
        memcpy(res, &this->updatecar, sizeof(this->updatecar));

        this->head.bussinesstype =5;
        this->head.bussinesslen = sizeof(this->updatecar);
        this->head.CRC= shareinfo->CalcCRCCode((unsigned char*)res, sizeof(this->updatecar));
        //send update and head to buf
        memset(buf,0,sizeof(buf));
        memcpy(buf,&this->head,sizeof(this->head));
        memcpy(buf+sizeof(this->head),&(this->updatecar),sizeof(this->updatecar));
        //set data
        this->wt->setData(this->buf,sizeof(this->head)+sizeof(this->updatecar));
        qDebug()<<"write info to server, type =5";


        this->ui->lineEdit_2->setReadOnly(true);
        this->ui->pushButton->setText("modify");
        this->modify_flag=0;
    }

}

//take photo for licence
void CCarInWin::on_pushButton_2_clicked()
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

           this-> q_image = QImage(car_number.data,car_number.cols,car_number.rows,QImage::Format_RGB888);
           ui->label_5->setPixmap(QPixmap::fromImage(q_image));
           ui->label_5->setScaledContents(true);

           string str_car_num = plateVec[0].getPlateStr();
           QString q_str = QString::fromLocal8Bit(str_car_num.c_str());
           ui->lineEdit_2->clear();
           ui->lineEdit_2->insert(q_str);

       }

       plateVec.clear();

       //set enter parking time
       this->ui->lineEdit->setText(this->time);
       //change current info
       emit SendCurrentInfo();
       //insert info to table
        this->firstplate = ui->lineEdit_2->text(); //plate number
        qDebug()<<"first = "<<this->firstplate;

       QMessageBox::information(this, "hint", "record ok");

       //save car picture
       //QString save_path = "./Image/" + shareinfo->getCurrenttime()+ ".png";
       this->SaveWaterPicture();


       //send info to server : new car
       memset(&this->car,0,sizeof(this->car));
       this->car.imageid=0;
       memcpy(this->car.filepath,this->save_path.toStdString().c_str(),sizeof(this->car.filepath));
       memcpy(this->car.plate,this->firstplate.toStdString().c_str(),sizeof(this->car.plate));
       memcpy(this->car.site,"western site",sizeof(this->car.site));
       memcpy(this->car.time,this->shareinfo->getCurrenttime().toStdString().c_str(),sizeof(this->car.time));
       //set head
       char res[1024]= {0};
       memcpy(res, &this->car, sizeof(this->car));

       this->head.bussinesstype = 4;
       this->head.CRC = shareinfo->CalcCRCCode((unsigned char*)res, sizeof(this->car));
       this->head.bussinesslen =sizeof(this->car);
       //set info to buf
       memset(this->buf,0,sizeof(this->buf));
       memcpy(this->buf,&(this->head),sizeof(this->head));
       memcpy(this->buf + sizeof(this->head),&(this->car),sizeof(this->car));
       //set data
       this->wt->setData(this->buf,sizeof(this->head)+sizeof(this->car));
       qDebug()<<"write date ok, type =4";


/*
       int row = this->ui->tableWidget->rowCount();
       qDebug()<<row;
       this->ui->tableWidget->insertRow(row);
       //add table : id plate time site

       this->ui->tableWidget->setItem(row,0,new QTableWidgetItem("1"));
       this->ui->tableWidget->setItem(row,1,new QTableWidgetItem(this->ui->lineEdit_2->text()));
       this->ui->tableWidget->setItem(row,2,new QTableWidgetItem(this->ui->lineEdit->text()));
       this->ui->tableWidget->setItem(row,3,new QTableWidgetItem("western site"));
*/

}

//car input video
void CCarInWin::updateImage(Mat frame)
{
    this->frame = frame.clone();
    cvtColor(this->frame,this->frame,CV_BGR2RGB);
//    cvtColor(this->frame,this->frame,CV_BGR2RGB);
    this->update(); //recall the event
}

//user +1 number -1
void CCarInWin::ChangeCurrentInfo()
{
    CCarInWin::current_user++;
    this->parking_current_num++;
    CCarInWin::parking_rest_num=this->parking_max_num-this->parking_current_num;
    this->shareinfo->setRestNum(this->parking_max_num-this->parking_current_num);
    this->shareinfo->setUserNum(CCarInWin::current_user);
//    qDebug()<<CCarInWin::parking_rest_num;
    QString restnum = QString::number((this->parking_max_num-this->parking_current_num),10);
    this->ui->lineEdit_3->setText(restnum);
    /*
    QString user = QString::number(CCarInWin::current_user,10);
    this->ui->lineEdit_4->setText(user);
    */
}

// get all info from server type = 7
void CCarInWin::doubleClickInfo(int row, int col)
{
    qDebug()<<row;
    //send info to server
    memset(&this->car, 0, sizeof(this->car));
    //row = i
    memcpy(car.plate, carin[row].plate, sizeof(car.plate));
    memset(&this->head, 0, sizeof(this->head));

    char res[1024] ={0};
    memcpy(res, &this->car, sizeof(this->car));

    this->head.bussinesstype = 7;
    this->head.CRC = shareinfo->CalcCRCCode((unsigned char*)res, sizeof(this->car));
    this->head.bussinesslen = sizeof(this->car);
    memset(buf,0,sizeof(buf));
    memcpy(this->buf, &(this->head), sizeof(this->head));
    memcpy(this->buf + sizeof(head), &this->car, sizeof(this->car));
    this->wt->setData(this->buf, sizeof(this->head)+sizeof(this->car));
    qDebug()<<"write ok and type = 7 ";

}

void CCarInWin::updateTable(REGISTER &reg, vector<CARIN> car)
{
    this->ui->tableWidget->removeRow(0);
    this->ui->tableWidget->removeRow(1);
    this->ui->tableWidget->removeRow(2);
    this->ui->tableWidget->removeRow(3);

    //copy reg struct
    memcpy(this->reg.userid,reg.userid,sizeof(this->reg.userid));
    memcpy(this->reg.username,reg.username,sizeof(this->reg.username));
    memcpy(this->reg.userpwd,reg.userpwd,sizeof(this->reg.userpwd));
    //set info to struct
    this->shareinfo->setUserName(this->reg.username); //user name
    this->shareinfo->setUserId(this->reg.userid); //user id
    this->ui->lineEdit_4->setText(this->reg.username);

    //copy vector
    this->carin.clear();
    for(int i=0; i<car.size(); i++) // size=<4
    {
        this->carin.push_back(car[i]);
    }

    //add info to table
    for(int i=0; i< this->carin.size(); i++)
    {
        int row = this->ui->tableWidget->rowCount();
        qDebug()<<row;
        this->ui->tableWidget->insertRow(row);
        QString car_id = QString::number(carin[i].imageid,10);
        this->ui->tableWidget->setItem(i,0,new QTableWidgetItem(car_id));
        this->ui->tableWidget->setItem(i,1,new QTableWidgetItem(carin[i].plate));
        this->ui->tableWidget->setItem(i,2,new QTableWidgetItem(carin[i].time));
        this->ui->tableWidget->setItem(i,3,new QTableWidgetItem(carin[i].site));
    }

    qDebug()<<"ui->tableWidget->rowCount() = "<<ui->tableWidget->rowCount();

}

//add new and modify will update the table
//type = 4
void CCarInWin::ChangeTable(vector<CARIN> car)
{
    //clear table and update it
//    this->ui->tableWidget->clear();
    for(int i=0; i < this->ui->tableWidget->rowCount(); i++)
    {
        qDebug()<<"car.size = "<< i;
        this->ui->tableWidget->removeRow(i);
    }

    //copy vector
    this->carin.clear();
    for(int i=0; i<car.size(); i++) // size=<4
    {
        this->carin.push_back(car[i]);
    }
    qDebug()<<"this->carin = "<<this->carin.size();

    //add info to table
    for(int i=0; i< this->carin.size(); i++)
    {
        //int row = this->ui->tableWidget->rowCount();
        //qDebug()<<row;
        this->ui->tableWidget->insertRow(i);
        QString car_id = QString::number(carin[i].imageid,10);
        this->ui->tableWidget->setItem(i,0,new QTableWidgetItem(car_id));
        this->ui->tableWidget->setItem(i,1,new QTableWidgetItem(carin[i].plate));
        this->ui->tableWidget->setItem(i,2,new QTableWidgetItem(carin[i].time));
        this->ui->tableWidget->setItem(i,3,new QTableWidgetItem(carin[i].site));
    }

}

//double click and new window
void CCarInWin::oneDetailCar(CARIN& car)
{
    OneCarWin *onecar = new OneCarWin(car);
    onecar->show();
}

//type = 6
void CCarInWin::getMoreCar(int flag, vector<CARIN> car)
{
    if(flag ==1)
    {
        qDebug()<<"more car to table";

        this->morecar.clear();
        for(int i=0; i<car.size(); i++) // size=<4
        {
            qDebug()<<i;
            this->morecar.push_back(car[i]);
        }
        //add to carin
        for(int i=0; i<morecar.size();i++)
        {
            this->carin.push_back(morecar[i]);
        }

        //add the table
        for(int i=0; i< this->morecar.size(); i++)
        {
            int row = this->ui->tableWidget->rowCount();
            qDebug()<<row;
            this->ui->tableWidget->insertRow(row);
            QString car_id = QString::number(morecar[i].imageid,10);
            this->ui->tableWidget->setItem(row,0,new QTableWidgetItem(car_id));
            this->ui->tableWidget->setItem(row,1,new QTableWidgetItem(morecar[i].plate));
            this->ui->tableWidget->setItem(row,2,new QTableWidgetItem(morecar[i].time));
            this->ui->tableWidget->setItem(row,3,new QTableWidgetItem(morecar[i].site));
        }

    }
    else if(flag ==0) //no more car
    {
        QMessageBox::information(this, "hint", "no more Car!");
    }
}

/*
       int row = this->ui->tableWidget->rowCount();
       this->ui->tableWidget->insertRow(row);
       //add table : id plate time site

       this->ui->tableWidget->setItem(row,0,new QTableWidgetItem("1"));
       this->ui->tableWidget->setItem(row,1,new QTableWidgetItem(this->ui->lineEdit_2->text()));
       this->ui->tableWidget->setItem(row,2,new QTableWidgetItem(this->ui->lineEdit->text()));
       this->ui->tableWidget->setItem(row,3,new QTableWidgetItem("western site"));
*/

//more 4 car
void CCarInWin::on_pushButton_3_clicked()
{
    this->page++;
    memset(&this->head,0,sizeof(this->head));
    memset(&this->load,0,sizeof(this->load));
    load.index = this->page;
    //set head
    char res[1024] ={0};
    memcpy(res, &this->load, sizeof(this->load));

    this->head.bussinesstype = 6;
    this->head.CRC= shareinfo->CalcCRCCode((unsigned char*)res, sizeof(this->load));
    this->head.bussinesslen = sizeof(this->load);
    //send head + load
    memset(this->buf,0,sizeof(this->buf));
    memcpy(this->buf,&(this->head),sizeof(this->head));
    memcpy(this->buf + sizeof(this->head), &(this->load), sizeof(this->load));
    //set data
    this->wt->setData(this->buf, sizeof(this->head) + sizeof(this->load));
    qDebug()<<"write ok and type = 6";
}

//one picture ok
void CCarInWin::getPictureOk(int flag)
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

void CCarInWin::get2PictureSave(int flag)
{
    if(flag ==0)
    {
        QMessageBox::information(this,"hint","save picture error");
    }
}

//first send car picture
void CCarInWin::CarPicture(QString filename)
{
    QString dir = "./TempFile";
    QString filepath = "./CarImage/" + this->picture_path + ".jpg";
    QString realname = filename + "ci";
    this->pt->setDirname(dir);
    this->pt->setFilename(filepath); //path
    this->pt->setPictureName(realname); //name
    this->pt->start(); //send car picture to server

}

//second send plate picture
void CCarInWin::PlatePicture(QString filename)
{
    QString dir = "./TempFile2/";
    QString filepath = "./CarInPlate/" + this->picture_path + ".jpg";
    QString realname = filename + "pi";
    this->pt->setDirname(dir);
    this->pt->setFilename(filepath); //path
    this->pt->setPictureName(realname); //name
    this->pt->start();

}
