#include "centerwin.h"
#include "ui_centerwin.h"
#include <QDebug>
#include <QMessageBox>
#include <stdio.h>
#include <string.h>
#include <QMessageBox>

CEnterWin::CEnterWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CEnterWin)
{
    ui->setupUi(this);
    //init some
    this->wt = WriteThread::getInstance();
    this->rt = ReadThread::getInstance();
    //clear specific
    memset(&this->head,0,sizeof(this->head));
    memset(&this->feed,0,sizeof(this->feed));
    memset(&this->login,0,sizeof(this->login));

    //edit input number  no word
    this->ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9a-zA-Z_]+$")));
    this->ui->lineEdit_2->setValidator(new QRegExpValidator(QRegExp("[0-9a-zA-Z_]+$")));
    //give user some hint
    this->ui->lineEdit->setPlaceholderText("8 max digit account");
    this->ui->lineEdit_2->setPlaceholderText("10 max digit password");
    this->ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    //limit length
    this->ui->lineEdit->setMaxLength(8);
    this->ui->lineEdit_2->setMaxLength(10);
    this->ui->lineEdit_3->setMaxLength(4);

    //this->mainwin = new MainWindow();
    this->mainwin = MainWindow::getInstence();
    this->regwin = new CRegWin();

    shareinfo = ShareInfo::getInstance();

    //thread connect
    connect(this->rt,SIGNAL(send2Enter(int)),this,SLOT(isCheck(int)));

}

CEnterWin::~CEnterWin()
{
    delete ui;
}

//enter system
void CEnterWin::on_pushButton_clicked()
{
    //give user some hints
    //account and passwd is/not empty
    if(this->ui->lineEdit->text().isEmpty())
    {
        QMessageBox::information(this, "hint", "account is empty",
                    QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    else if(this->ui->lineEdit_2->text().isEmpty())
    {
        QMessageBox::information(this, "hint", "password is empty",
                    QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    else if(this->ui->lineEdit_3->text().isEmpty())
    {
        QMessageBox::information(this, "hint", "verfication code is empty",
                    QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    else if(QString::compare(this->ui->label_5->getVerificationCode(),this->ui->lineEdit_3->text())!=0) //no match verification code
    {
        QMessageBox::information(this, "hint", "verfication code is wrong");
    }
    else // all ok
    {

        //write thread to server and start read
        //get info
        /*
        const char*pname = this->ui->lineEdit->text().toStdString().c_str();
//        const char*ppwd = this->ui->lineEdit_2->text().toStdString().c_str();
        //md5
        String str;
        MD5 md;
        str = md.Encode(this->ui->lineEdit_2->text().toStdString());
        const char*ppwd = str.c_str();
        */
        char pname[20]={0};
        char ppwd[40]={0};
        QString test = ui->lineEdit->text();
        memcpy(pname,test.toStdString().c_str(),sizeof(pname));
        test = ui->lineEdit_2->text();
        //memcpy(ppwd, test.toStdString().c_str(),sizeof(ppwd));
        MD5 md;
        String str = md.encode(test.toStdString());
        memcpy(ppwd,str.c_str(),sizeof(ppwd));

        /*
        String str;
        MD5 md;
        test = ui->lineEdit_2->text();
        str = md.Encode(test.toStdString());
        memcpy(ppwd,str.c_str(),sizeof(ppwd));
        */

        //send info to login
        memcpy(login.userid, pname, sizeof(login.userid));
        memcpy(login.userpwd, ppwd, sizeof(login.userpwd));

        //test
        qDebug()<<"login.userid"<<login.userid;
        qDebug()<<"login.userpwd"<<login.userpwd;

        char res[1024] = {0};
        memcpy(res, &login, sizeof(login));

        //set head
        this->head.bussinesstype = 2;
        this->head.CRC = shareinfo->CalcCRCCode((unsigned char*)res, sizeof(login));
        this->head.bussinesslen = sizeof(this->login);
        //send login and head to buf
        memset(buf,0,sizeof(this->buf));
        memcpy(this->buf,&(this->head),sizeof(this->head));
        memcpy(this->buf + sizeof(this->head),&(this->login),sizeof(this->login));
        //set data and start
        this->wt->setData(this->buf,sizeof(this->head)+ sizeof(this->login));

        qDebug()<<"ok";
    }

    //match verification code
    //QString code = this->ui->label_5->getVerificationCode();
    //get edit content
    //QString content = this->ui->lineEdit_3->text();
}

//judge enter system
void CEnterWin::isCheck(int flag)
{
    if(flag == 0 )
    {
        qDebug()<<"fail enter system";
        QMessageBox::warning(this, "hint", "fail enter");

    }
    else if(flag ==1 )
    {
        qDebug()<<"successfully enter system";
        //QMessageBox::information(this, "hint", "successfully enter");

        qDebug()<<" isCheck(int flag) !!";
        this->close();
        this->mainwin->show();

    }
}

//register
void CEnterWin::on_pushButton_2_clicked()
{
    //must close x hide
    this->close();
    this->regwin->show();
}
