#include "cvideoplayer.h"
#include "ui_cvideoplayer.h"
#include <QDebug>

CVideoPlayer::CVideoPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CVideoPlayer)
{
    ui->setupUi(this);
    //init something
    this->count=0;
    this->flag=0;
    this->ui->lineEdit->setFocusPolicy(Qt::NoFocus); //prohibit press

    qRegisterMetaType<Mat>("Mat");
//    qRegisterMetaType<Pos>("Pos");
    this->vthread = new VideoThread();
    //this->vthread->start();
    connect(this->vthread,SIGNAL(sendFrame2Win(Mat, int)),this,SLOT(getFrame(Mat, int)),Qt::BlockingQueuedConnection);
    connect(this,SIGNAL(changeFlag()),this->vthread,SLOT(getFlag())); //stop and start video
    connect(this->vthread,SIGNAL(send2Win_Count(double)),this,SLOT(getCount(double)));//count of video
    connect(this,SIGNAL(sendValue(int)),this->vthread,SLOT(getValue(int))); //change process value
    connect(this->ui->comboBox,SIGNAL(currentIndexChanged (int)),this->vthread,SLOT(getSpeed(int))); //speed of video x2 x1
}

void CVideoPlayer::setVideoPath(QString filename)
{
    //QString file_path = "./ParkVideo/" + filename + ".avi";
    //QString file_path = "./ParkVideo/2022-07-22 07:01:11.avi";
    this->vthread->setVideoName(filename);
    this->vthread->start();
}

CVideoPlayer::~CVideoPlayer()
{
    delete ui;
}

//close window
void CVideoPlayer::closeEvent(QCloseEvent *event)
{
//    this->vthread->wait(); //stop thread
    this->vthread->quit();//stop thread
//    qDebug()<<this->frame_num;
    qDebug()<<"closeEvent(QCloseEvent *event) = "<<this->frame_num;
    emit sendRatio(this->frame_num);
}

//start video
void CVideoPlayer::on_pushButton_clicked()
{
    //change pushbutton text : start / stop
    if(this->flag ==1)
    {
        this->ui->pushButton->setText("stop");
        this->flag=0;
    }
    else if(this->flag==0)
    {
        this->ui->pushButton->setText("start");
        this->flag=1;
    }

    emit changeFlag();
}

//change slider value
void CVideoPlayer::on_horizontalSlider_valueChanged(int value)
{
    emit sendValue(this->ui->horizontalSlider->value());
}

/*
    this->q_image = QImage(frame.data,frame.cols,frame.rows,QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(q_image));
    ui->label->setScaledContents(true);
*/


void CVideoPlayer::getFrame(Mat frame, int num)
{
    //change label
    /*
    Mat processmat;
    QImage nextimage;
    QImage processimage;
    cvtColor(frame, processmat, CV_BGR2RGB);
    nextimage = QImage((const unsigned char*)(processmat.data),
                            processmat.cols, processmat.rows,
                            processmat.cols * processmat.channels(),
                            QImage::Format_RGB888);
    processimage = nextimage.scaled(ui->label->size(),Qt::KeepAspectRatio);
    this->ui->label->setPixmap(QPixmap::fromImage(processimage));
    */
    Mat res = frame.clone();
    cvtColor(res,res,CV_BGR2RGB);
    QImage q_image = QImage(res.data,frame.cols,res.rows,QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(q_image));
    ui->label->setScaledContents(true);

    //change slider
    this->frame_num = num;
    this->ui->horizontalSlider->setValue(num);

    //edit : the process of video  eg. 14/700
    char name[30];
    sprintf(name, "%d/%d", num, this->count);
    this->ui->lineEdit->setText(name);

    this->update();
}

void CVideoPlayer::getCount(double count)
{
    this->count = (int)count;
    //set slider range
    this->ui->horizontalSlider->setRange(0,count);
}

void CVideoPlayer::setValue(int value)
{
    this->vthread->setValue(value);
}
