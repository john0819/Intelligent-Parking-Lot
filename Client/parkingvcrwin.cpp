#include "parkingvcrwin.h"
#include "ui_parkingvcrwin.h"
#include <QMessageBox>

ParkingVCRWin::ParkingVCRWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParkingVCRWin)
{
    ui->setupUi(this);
    //init some
    shareinfo = ShareInfo::getInstance();
    /*
    QString user = QString::number(shareinfo->getUserNum(),10) + "  cars";
    QString rest = QString::number(shareinfo->getRestNum(),10);
    this->ui->lineEdit->setText(user);
    this->ui->lineEdit_2->setText(rest);
    */
    this->ui->lineEdit->setFocusPolicy(Qt::NoFocus);
    this->ui->lineEdit_2->setFocusPolicy(Qt::NoFocus);
    this->ui->lineEdit->setStyleSheet("color:red");
    this->ui->lineEdit_2->setStyleSheet("color:red");

    this->stopflag =1;
    this->autoflag=0;
    this->Mtimer = new QTimer();
    connect(this->Mtimer,SIGNAL(timeout()),this,SLOT(CreateMutualVideo())); //create video
    this->Atimer = new QTimer();
    connect(this->Atimer,SIGNAL(timeout()),this,SLOT(CreateAutoVideo()));

    //init some
    this->rt = ReadThread::getInstance();
    this->wt = WriteThread::getInstance();
    memset(&this->parkinfo,0,sizeof(this->parkinfo));
    memset(&this->videoinfo,0,sizeof(this->videoinfo));


    //mark
    this->Mark = imread("./Image/logo2.png");

    //play video
    this->parkthread = new ParkingThread("./Video/Parking_lot2.mp4");
    qRegisterMetaType<Mat>("Mat");
    qRegisterMetaType<PARKINFO>("PARKINFO&");
    connect(this->parkthread,SIGNAL(frameVideo(Mat)),this,SLOT(updateImage(Mat)),Qt::BlockingQueuedConnection);

    connect(this->rt,SIGNAL(send2ParkInfo(int, PARKINFO&)),this,SLOT(getParkInfo(int, PARKINFO&)));

    //know whether ok(record video)
    connect(this->rt,SIGNAL(send2Video(int)),this,SLOT(getVideoRecord(int)));

    //init writer
    /*
    this->frame_fps=25;
    this->frame_width=640;
    this->frame_height=480;
    this->frame_num=0;
    */
    //this->writer = VideoWriter("./Video/test.avi", CV_FOURCC('M', 'J', 'P', 'G'),
            //frame_fps, Size(frame_width, frame_height),true);
 //   this->writer.open("./Video/test.avi",VideoWriter::fourcc('M', 'J', 'P', 'G'),25,Size(640, 480), true);

}

ParkingVCRWin::~ParkingVCRWin()
{
    delete ui;
}

//clear the queue
void ParkingVCRWin::clearQueue(queue<Mat> &que)
{
    queue<Mat>empty; //empty queue
    swap(empty, que);
}

void ParkingVCRWin::StartThread()
{
    qDebug()<<"start ParkingVCRWin";
    this->parkthread->start();
}

//save video
void ParkingVCRWin::SetFrameSize(QString filename)
{
    this->frame_height = this->frame.rows;
    this->frame_width = this->frame.cols;
    qDebug()<<frame_width;
    qDebug()<<frame_height;
    this->video_name = "./ParkVideo/" + filename + ".avi";
    this->writer.open(this->video_name.toStdString().c_str(),VideoWriter::fourcc('M', 'J', 'P', 'G'),25,Size(frame_width, frame_height), true);
}

//first picture
void ParkingVCRWin::SavePicture(QString filename)
{
    this->picture_name = "./ParkImage/" + filename+ ".png";
    qDebug()<<"picture name ="<<this->picture_name;
    Mat waterMark = this->frame.clone();
    Mat Mark = imread("./Image/logo2.png");
    Mat result;
    cv::resize(Mark, Mark, Size(waterMark.cols, waterMark.rows),0, 0, INTER_CUBIC);
    addWeighted(waterMark,1.0,Mark,0.3,0,result);
    QImage res = QImage(result.data,result.cols,result.rows,QImage::Format_RGB888);
    res.save(this->picture_name,"PNG",100);
}

//send to server
void ParkingVCRWin::Send2Server()
{
    //count
    VideoCapture cap(this->video_name.toStdString().c_str());
    int video_count = (int)cap.get(7);
    qDebug()<<"video_count = "<<video_count;

    //type == 11
    memset(&this->videoinfo,0,sizeof(this->videoinfo));
    QString video_name_is = this->now_time_is + ".avi"; //video name

    //month + day
    QStringList str1 = this->now_time_is.split(" ");
    QString res = str1[0]; //2022-07-27

    //month
    QStringList str2 = res.split("-");
    QString month = str2[0] + "-" + str2[1]; //2022-07
    QString day = str2[2];

    memcpy(this->videoinfo.videoname,video_name_is.toStdString().c_str(),sizeof(this->videoinfo.videoname));
    this->videoinfo.video_count = video_count;
    this->videoinfo.video_num = 0;
    memcpy(this->videoinfo.video_path, this->video_name.toStdString().c_str(),sizeof(this->videoinfo.video_path));
    memcpy(this->videoinfo.picutre_path, this->picture_name.toStdString().c_str(),sizeof(this->videoinfo.picutre_path));
    memcpy(this->videoinfo.date,day.toStdString().c_str(),sizeof(this->videoinfo.date));
    memcpy(this->videoinfo.month,month.toStdString().c_str(),sizeof(this->videoinfo.month));

    //set head
    char buf2[1024]={0};
    memcpy(buf2, &this->videoinfo, sizeof(this->videoinfo));

    memset(&this->head,0,sizeof(this->head));
    this->head.bussinesslen = sizeof(this->videoinfo);
    this->head.CRC=shareinfo->CalcCRCCode((unsigned char*)buf2,sizeof(this->videoinfo));
    this->head.bussinesstype = 11;
    //send info and head to buf
    memset(this->buf,0,sizeof(this->buf));
    memcpy(this->buf, &(this->head), sizeof(this->head));
    memcpy(this->buf + sizeof(this->head), &(this->videoinfo), sizeof(this->videoinfo));
    //set data
    this->wt->setData(this->buf, sizeof(this->head) + sizeof(this->videoinfo));
    qDebug()<<"write server and type = 11";

}

void ParkingVCRWin::paintEvent(QPaintEvent *e)
{
    this->q_image = QImage(frame.data,frame.cols,frame.rows,QImage::Format_RGB888);
    ui->label_2->setPixmap(QPixmap::fromImage(q_image));
    ui->label_2->setScaledContents(true);

    /*
    //test : see number of mat
    if(this->stopflag == 0)
    {
        this->save_path = "./Image/" + shareinfo->getCurrenttime() + ".png";
        this->q_image.save(this->save_path,"PNG",100);
    }
    */
}

//save image snapshot
//add watermark to picture
void ParkingVCRWin::on_pushButton_clicked()
{
    this->save_path = "./SnapImage/" + shareinfo->getCurrenttime()+ ".png";
    /*
    this->save_path = "./Image/" + shareinfo->getCurrenttime()+ ".png";
    this->q_image.save(this->save_path,"PNG",100);
    */
    this->waterMark = this->frame.clone();
    Mat result;
    cv::resize(this->Mark, this->Mark, Size(this->waterMark.cols, this->waterMark.rows),0, 0, INTER_CUBIC);
    addWeighted(this->waterMark,1.0,this->Mark,0.3,0,result);
    QImage res = QImage(result.data,result.cols,result.rows,QImage::Format_RGB888);
    res.save(this->save_path,"PNG",100);
}

void ParkingVCRWin::updateImage(Mat frame)
{
    this->frame = frame.clone();
    cvtColor(this->frame,this->frame,CV_BGR2RGB);

    //get mat to queue
    if(this->stopflag == 0)
    {
        //test
        Mat res = this->frame.clone();
        cvtColor(res,res,CV_BGR2RGB);
        this->writer.write(res);
    }
    //auto record
    if(this->autoflag == 1)
    {
        Mat autores = this->frame.clone();
        cvtColor(autores,autores,CV_BGR2RGB);
        this->writer.write(autores);
    }

}

//create video for 30s
//1s only send 1 picture
void ParkingVCRWin::on_pushButton_2_clicked()
{
    //save image for video(first)
    QString filename = this->shareinfo->getCurrenttime();
    this->now_time_is = filename;
    //save picture
    this->SavePicture(filename);
    //save video
    this->SetFrameSize(filename); //set size
    this->stopflag=0;
    this->Mtimer->start(10000); //5s

    //cant press auto
    this->ui->checkBox->setEnabled(false);
}

void ParkingVCRWin::CreateMutualVideo()
{
    qDebug()<<"time out ";

    this->writer.release(); //aviod lost
    this->stopflag=1;
    this->Mtimer->stop();
    this->ui->checkBox->setEnabled(true);

    //send server type =11
    this->Send2Server();


/*
    for(int i=0; i<this->frame_num; i++)
    {
        //this->writer <<
        this->videoFrame = videoqueue.front();
        this->writer << this->videoFrame;
    }
*/
//    this->clearQueue(this->videoqueue);

    //test
    /*
    Mat frame;
    VideoCapture cap("./Video/Parking_lot2.mp4");
    while(cap.read(frame))
    {
        writer.write(frame);
    }
    */

    /*
    //test
    //sprintf video
    for(int i=0; i<this->frame_num; i++)
    {
        //this->writer <<
        this->videoFrame = videoqueue.front();
        this->writer << this->videoFrame;
    }
    this->clearQueue(this->videoqueue);
    */
}


//automatically record the video (button press)
void ParkingVCRWin::CreateAutoVideo()
{
    qDebug()<<"one video";
    this->writer.release();
    //send to server

    //new one more
    //update the writer
    QString filename = this->shareinfo->getCurrenttime();
    this->now_time_is = filename;
    //save picture
    this->SavePicture(filename);
    //save video
    this->SetFrameSize(filename); //set size

    //send server type =11
    this->Send2Server();

    /*
    for(int i=0; i<this->AutoQueue.size(); i++) //30s
    {

        this->writer<<this->AutoQueue.front();
    }
    this->clearQueue(this->AutoQueue);
    */
}

//auto record video
void ParkingVCRWin::on_checkBox_clicked(bool checked)
{
    this->clearQueue(this->videoqueue);
    if(checked == true) //automatically record
    {
        this->ui->pushButton_2->setEnabled(false); //cant press btn (mutual)

        //save picture
        QString filename = this->shareinfo->getCurrenttime();
        this->now_time_is = filename;
        //save picture
        this->SavePicture(filename);
        //save video
        this->SetFrameSize(filename); //set size

        qDebug()<<"checked ok";
        //this->writer.open(); //new file
        this->autoflag=1; //record video auto
        this->Atimer->start(30000); //30s video
    }
    else if(checked == false) //stop auto
    {
        this->ui->pushButton_2->setEnabled(true);

        qDebug()<<"no automatical";
        this->autoflag=0;
        this->Atimer->stop();
    }
}

void ParkingVCRWin::getParkInfo(int flag, PARKINFO &park)
{
    if(flag ==1)
    {
        // 1 user 2 rest
        QString user = QString::number(park.occupy,10) + "  cars";
        QString rest = QString::number(park.leisure,10);
        this->ui->lineEdit->setText(user);
        this->ui->lineEdit_2->setText(rest);
        //update the shareinfo
        shareinfo->setUserNum(park.occupy);
        shareinfo->setRestNum(park.leisure);
    }

}

void ParkingVCRWin::getVideoRecord(int flag)
{
    if(flag ==1)
    {
        QMessageBox::information(this,"hint","send video ok");
    }
    else if(flag==0)
    {
        QMessageBox::information(this,"hint","send video unsuccessfully");
    }
}
