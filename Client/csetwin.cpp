#include "csetwin.h"
#include "ui_csetwin.h"
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include "mainwindow.h"

QString CSetWin::PicturePath;
QString CSetWin::VideoPath;

CSetWin::CSetWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSetWin)
{
    ui->setupUi(this);
    //init some
    this->sc = SocketConnect::getInstance();
    this->wt = WriteThread::getInstance();
    this->rt = ReadThread::getInstance();

    this->enterWin = new CEnterWin();

    //edit input number  no word
    this->ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9.]+$")));
    this->ui->lineEdit_2->setValidator(new QRegExpValidator(QRegExp("[0-9]+$")));
    //give user some hint
    this->ui->lineEdit->setPlaceholderText("please input number");
    this->ui->lineEdit_2->setPlaceholderText("please input number");
    this->ui->lineEdit_5->setPlaceholderText("please input number");

    //edit cant input
    this->ui->lineEdit_3->setFocusPolicy(Qt::NoFocus);
    this->ui->lineEdit_4->setFocusPolicy(Qt::NoFocus);

    //shareinfo
    this->shareinfo = ShareInfo::getInstance();

    //judge
    this->JudgeFirst();
}

//get important role
QString CSetWin::getPicturePath()
{
    return CSetWin::PicturePath;
}

QString CSetWin::getVideoPath()
{
    return CSetWin::VideoPath;
}

//judge user first enter system
void CSetWin::JudgeFirst()
{
    int flag = 0;
    //read (info) file and save info to info (vector)
    QFile file("./Cascade/setinfo.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        while (!file.atEnd())
        {
            QStringList list = stream.readAll().split("\n");
            QListIterator<QString> li(list);
            QString str;
            while(li.hasNext())
            {
                str=li.next();
                this->info.push_back(str);
                flag++;
            }
        }
    }

    //judge info
    if(flag!=0)  //x first
    {
        QString picture_path = info[2];
        QString video_path = info[3];
        qDebug()<<picture_path;
        qDebug()<<video_path;
        QDir picture_dir;
        QDir video_dir;
        if(picture_dir.exists(picture_path) && video_dir.exists(video_path)) //if exist
        {
            qDebug()<<"exist";

            this->ui->lineEdit->setText(info[0]);
            this->ui->lineEdit_2->setText(info[1]);
            this->ui->lineEdit_3->setText(info[2]);
            this->ui->lineEdit_4->setText(info[3]);
            this->ui->lineEdit_5->setText(info[4]);


        }
        else
        {
            qDebug()<<"no, it is first";
        }
    }

}

//update the shareinfo : ip/ host/ address/ gb
void CSetWin::Send2Share()
{
    this->shareinfo->setIp(this->info[0]);
    this->shareinfo->setHost(this->info[1]);
    this->shareinfo->setPicture(this->info[2]);
    this->shareinfo->setVideo(this->info[3]);
    this->shareinfo->setSize(this->info[4]);
}

CSetWin::~CSetWin()
{
    delete ui;
}

//choose picture saving address
void CSetWin::on_pushButton_3_clicked()
{
    this->PicturePath = QFileDialog::getExistingDirectory();
    this->ui->lineEdit_3->setText(this->PicturePath);
}

//choose video saving adress
void CSetWin::on_pushButton_4_clicked()
{
    this->VideoPath=QFileDialog::getExistingDirectory();
    this->ui->lineEdit_4->setText(this->VideoPath);
}


//yse : save to file
void CSetWin::on_pushButton_clicked()
{
    //give some hint
    if(this->ui->lineEdit->text().isEmpty())
    {
        QMessageBox::warning(this, "hint", "Ip is empty");
    }
    else if(this->ui->lineEdit_2->text().isEmpty())
    {
        QMessageBox::warning(this, "hint", "host is empty");
    }
    else if(this->ui->lineEdit_3->text().isEmpty())
    {
        QMessageBox::warning(this, "hint", "picture address is empty");
    }
    else if(this->ui->lineEdit_4->text().isEmpty())
    {
        QMessageBox::warning(this, "hint", "video address is empty");
    }
    else if(this->ui->lineEdit_5->text().isEmpty())
    {
        QMessageBox::warning(this, "hint", "GB size is empty");
    }
    else // all ok
    {
        QFile file("./Cascade/setinfo.txt");
        if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Truncate)) //QIODevice::Truncate : must be renew the file
        {
            QTextStream stream(&file);
            stream<<this->ui->lineEdit->text()<<"\n";
            stream<<this->ui->lineEdit_2->text()<<"\n";
            stream<<this->ui->lineEdit_3->text()<<"\n";
            stream<<this->ui->lineEdit_4->text()<<"\n";
            stream<<this->ui->lineEdit_5->text()<<"\n";
        }
        this->Send2Share();
        qDebug()<<"write ok!";

        //later use

        //start connect and thread
        //connect
        this->sc->setIp(this->info[0]);
        this->sc->setHost(this->info[1].toInt());
        this->sc->CreateConnect();
        //thread set
        this->wt->setSocketfd(this->sc->getSocketfd());
        this->rt->setSocketfd(this->sc->getSocketfd());
        this->wt->start();
        this->rt->start();

        //judget connect ok
        if(this->sc->getFlag() == 1)
        {
            qDebug()<<"socket connect ok and init thread";
            QMessageBox::information(this, "hint", "successfully connect");
        }
        else if(this->sc->getFlag() == 0)
        {
            qDebug()<<"connect error";
            QMessageBox::information(this, "hint", "fail to connect");
        }

        this->hide();
        this->enterWin->show();

    }

    //create file
    /*
    QFile temp_path("./Cascade/setinfo.txt");
    QDir dir;
    //first: no file
    if(!dir.exists("./Cascade/setinfo.txt"))
    {
        temp_path.open(QIODevice::ReadWrite); //create a txt which can be read and write
    }
    */
    /*
    //read file and save info to info (vector)
    int i=0;
    QFile file("./Cascade/setinfo.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        while (!file.atEnd())
        {
            QStringList list = stream.readAll().split("\n");
            QListIterator<QString> li(list);
            QString str;
            while(li.hasNext())
            {
                str=li.next();
                this->info.push_back(str);
            }
        }
    }
    qDebug()<<info[0];
    */
    /*
    //write info to txt
    QFile file("./Cascade/setinfo.txt");
    if(file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
    {
        QTextStream stream(&file);
        stream<<"111\n";
        stream<<"222\n";
        stream<<"333\n";
    }
    */
}
//
void CSetWin::on_pushButton_2_clicked()
{
    this->close();
}
