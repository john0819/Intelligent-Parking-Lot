#include "cregwin.h"
#include "ui_cregwin.h"
#include <QMessageBox>
#include <QDebug>
#include<string.h>
#include "centerwin.h"
#include <QDebug>
#include <stdlib.h>
#include <string.h>

CRegWin::CRegWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CRegWin)
{
    ui->setupUi(this);
    this->flag=0;

    //edit input number  no word
    this->ui->lineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9a-zA-Z_]+$")));
    this->ui->lineEdit_2->setValidator(new QRegExpValidator(QRegExp("[0-9a-zA-Z_]+$")));
    //give user some hint
    this->ui->lineEdit->setPlaceholderText("8 max digit account");
    this->ui->lineEdit_2->setPlaceholderText("10 max digit password");
    //limit length
    this->ui->lineEdit->setMaxLength(8);
    this->ui->lineEdit_2->setMaxLength(8);
    this->ui->lineEdit_3->setMaxLength(10);
    this->ui->lineEdit_4->setMaxLength(10);
    //hide the password
    this->ui->lineEdit_3->setEchoMode(QLineEdit::Password);
    this->ui->lineEdit_4->setEchoMode(QLineEdit::Password);

    //init some
    this->wt =WriteThread::getInstance();
    this->rt = ReadThread::getInstance();
    //clear some
    memset(&this->head,0,sizeof(this->head));
    memset(&this->feed,0,sizeof(this->feed));
    memset(&this->reg,0,sizeof(this->reg));

    //init window
    shareinfo = ShareInfo::getInstance();

    //connect
    connect(this->rt,SIGNAL(send2RigWidget(int)),this,SLOT(isChecked(int)));
}

CRegWin::~CRegWin()
{
    delete ui;
}

void CRegWin::on_pushButton_3_clicked()
{
    this->flag++;
    if(this->flag % 2 == 1)
    {
        this->ui->lineEdit_3->setEchoMode(QLineEdit::Normal);
        this->ui->lineEdit_4->setEchoMode(QLineEdit::Normal);
    }
    else {
        this->ui->lineEdit_3->setEchoMode(QLineEdit::Password);
        this->ui->lineEdit_4->setEchoMode(QLineEdit::Password);
    }

}

//enter system
void CRegWin::on_pushButton_clicked()
{

    //empty is or not
    if(this->ui->lineEdit->text().isEmpty())
    {
        QMessageBox::information(this, "hint", "account is empty",
                    QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    else if(this->ui->lineEdit_2->text().isEmpty())
    {
        QMessageBox::information(this, "hint", "name is empty",
                    QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    else if(this->ui->lineEdit_3->text().isEmpty())
    {
        QMessageBox::information(this, "hint", "password code is empty",
                    QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }  
    else if(this->ui->lineEdit->text().length()<6) //check the min of account and password
    {
        QMessageBox::information(this, "hint", "account is short");
    }
    else if (this->ui->lineEdit_2->text().length()<6)
    {
        QMessageBox::information(this, "hint", "user name is short");
    }
    else if (this->ui->lineEdit_3->text().length()<6)
    {
        QMessageBox::information(this, "hint", "password is short");
    }
    else if (this->ui->lineEdit_4->text().length()<6)
    {
        QMessageBox::information(this, "hint", "password is short");
    }
    else if(QString::compare(this->ui->lineEdit_3->text().toStdString().c_str(),this->ui->lineEdit_4->text().toStdString().c_str()) != 0) //match password and password again
    {
        QMessageBox::information(this, "hint", "check the password again");
    }
    else //all ok
    {
        /*
        const char*pid = this->ui->lineEdit->text().toStdString().c_str();
        const char*pname = this->ui->lineEdit_2->text().toStdString().c_str();
        const char*ppwd = this->ui->lineEdit_3->text().toStdString().c_str();
        */
        char pname[20]={0};
        char pid[20]={0};
        char ppwd[40]={0};
        QString test = ui->lineEdit->text();
        memcpy(pid,test.toStdString().c_str(),sizeof(pid));
        test = ui->lineEdit_2->text();
        memcpy(pname,test.toStdString().c_str(),sizeof(pname));
        test = ui->lineEdit_3->text();
        //memcpy(ppwd,test.toStdString().c_str(),sizeof(ppwd));
        MD5 md;
        String str = md.encode(test.toStdString());
        memcpy(ppwd,str.c_str(),sizeof(ppwd));

        /*
        String str;
        MD5 md;
        test = ui->lineEdit_3->text();
        str = md.Encode(test.toStdString());
        memcpy(ppwd,str.c_str(),sizeof(ppwd));
        */
        //md5
        /*
        String str;
        MD5 md;
        str = md.Encode(this->ui->lineEdit_3->text().toStdString());
        const char*ppwd = str.c_str();
        */
        //send info to reg
        memcpy(reg.userid,pid,sizeof(reg.userid));
        memcpy(reg.username,pname,sizeof(reg.username));
        memcpy(reg.userpwd,ppwd,sizeof(reg.userpwd));

        //test
        qDebug()<<"reg.userid"<<reg.userid;
        qDebug()<<"reg.username"<<reg.username;
        qDebug()<<"reg.userpwd"<<reg.userpwd;

        char res[1024]={0};
        memcpy(res, &reg, sizeof(reg));

        //set head
        this->head.bussinesstype=1;
        this->head.CRC= shareinfo->CalcCRCCode((unsigned char*)res, sizeof(reg));
        this->head.bussinesslen=sizeof(this->reg);
        //send reg and head to buf
        memset(buf,0,sizeof(buf));
        memcpy(this->buf,&(this->head),sizeof(this->head));
        memcpy(this->buf + sizeof(this->head),&(this->reg),sizeof(this->reg));
        //set date
        this->wt->setData(this->buf,sizeof(this->head)+sizeof(this->reg));
        qDebug()<<"reg ok";
    }

}

//cacel : return enter window
void CRegWin::on_pushButton_2_clicked()
{
    this->enter = new CEnterWin();
    this->hide();
    this->enter->show();
}

void CRegWin::isChecked(int flag)
{
    if(flag == 0 )
    {
        qDebug()<<"fail register system";
        QMessageBox::information(this, "hint", "fail register");

    }
    else if(flag ==1 )
    {
        qDebug()<<"successfully register system";
        QMessageBox::information(this, "hint", "successfully register");

        this->enter = new CEnterWin();
        this->close();
        //return enroll
        this->enter->show();
    }
}
