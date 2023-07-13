#include "csearchwin.h"
#include "ui_csearchwin.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>
#include <vector>
#include <QMessageBox>
using namespace std;

CSearchWin::CSearchWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSearchWin)
{
    ui->setupUi(this);
    //init
    this->page=0;
    //set the count of rows and columns
    this->ui->tableWidget->setColumnCount(7);
//    this->ui->tableWidget->setRowCount(5);

    qRegisterMetaType<vector<CINFO>>("vector<CINFO>&");

    //fill in the table
    this->ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //calendar
    this->calendar = new QCalendarWidget();
    this->calendar1=new QCalendarWidget();
    calendar->setGeometry(this->ui->lineEdit_2->x(),this->ui->lineEdit_2->y()+10,300,200);
    calendar->setGeometry(this->ui->lineEdit_3->x(),this->ui->lineEdit_3->y()+10,300,200);

    qRegisterMetaType<vector<CINFO>>("vector<CINFO>");

    //show calendar connect
    connect(this->ui->lineEdit_2,SIGNAL(clicked()),this,SLOT(getClicked()));
    connect(this->ui->lineEdit_3,SIGNAL(clicked()),this,SLOT(getClicked1()));
    //select time
    connect(this->calendar,SIGNAL(clicked(const QDate &)),this,SLOT(selectDate(const QDate &)));
    connect(this->calendar1,SIGNAL(clicked(const QDate &)),this,SLOT(selectDate1(const QDate &)));

    //init some
    this->rt = ReadThread::getInstance();
    this->wt = WriteThread::getInstance();
    memset(&this->carout, 0, sizeof(this->carout));
    memset(&this->head,0,sizeof(this->head));

    //init
    this->shareinfo = ShareInfo::getInstance();

    connect(this->rt, SIGNAL(send2SearchData(int, vector<CINFO>)), this, SLOT(getDataInfo(int, vector<CINFO>)));
    connect(this->rt, SIGNAL(send2SearchMore(int, vector<CINFO>)), this, SLOT(getMoreInfo(int, vector<CINFO>)));
    //qDebug()<<this->ui->tableWidget->rowCount();
}

CSearchWin::~CSearchWin()
{
    delete ui;
}

//show
void CSearchWin::getClicked()
{
    //show calendar
    calendar->show();
//    qDebug()<<calendar->selectedDate().toString("yyyy-MM-dd");
}

void CSearchWin::getClicked1()
{
    calendar1->show();
}

void CSearchWin::selectDate(const QDate &data)
{
    this->ui->lineEdit_2->setText(data.toString("yyyy-MM-dd"));
    calendar->hide();
}

void CSearchWin::selectDate1(const QDate &data)
{
    this->ui->lineEdit_3->setText(data.toString("yyyy-MM-dd"));
    calendar1->hide();
}

//get info
void CSearchWin::getDataInfo(int flag, vector<CINFO> info)
{
    if(flag ==1) //have data
    {
        for(int i=0;i<this->ui->tableWidget->rowCount();i++)
        {
            this->ui->tableWidget->removeRow(i);
        }

        this->vec_car.clear();
        for(int i=0; i<info.size(); i++)
        {
            qDebug()<<"i = "<<i;
            this->vec_info.push_back(info[i]);

        }

        for(int i=0; i<info.size();i++)
        {
            if(QString(info[i].plate).isEmpty())
            {
                break;
            }
            QString id = QString::number(i,10);
            QString Money = QString::number(info[i].charge,10);
            this->ui->tableWidget->insertRow(i);
            this->ui->tableWidget->setItem(i,0,new QTableWidgetItem(id));
            this->ui->tableWidget->setItem(i,1,new QTableWidgetItem(info[i].plate));
            this->ui->tableWidget->setItem(i,2,new QTableWidgetItem(info[i].in_time));
            this->ui->tableWidget->setItem(i,3,new QTableWidgetItem(info[i].out_time));
            this->ui->tableWidget->setItem(i,4,new QTableWidgetItem(QIcon(info[i].in_path),""));
            this->ui->tableWidget->setItem(i,5,new QTableWidgetItem(QIcon(info[i].out_path),""));
            this->ui->tableWidget->setItem(i,6,new QTableWidgetItem(Money));
        }
    }
    else if(flag ==0)
    {
        QMessageBox::information(this,"hint","no such data");
    }
}

void CSearchWin::getMoreInfo(int flag, vector<CINFO> info)
{
    if(flag ==1)
    {
        for(int i=0; i<info.size(); i++)
        {
            this->vec_info.push_back(info[i]);
        }

        for(int i=0; i<info.size();i++)
        {
            if(QString(info[i].plate).isEmpty())
            {
                break;
            }


            int row = this->ui->tableWidget->rowCount();
            QString id = QString::number(i+row,10);
            QString Money = QString::number(info[i].charge,10);
            this->ui->tableWidget->insertRow(row);
            this->ui->tableWidget->setItem(row,0,new QTableWidgetItem(id));
            this->ui->tableWidget->setItem(row,1,new QTableWidgetItem(info[i].plate));
            this->ui->tableWidget->setItem(row,2,new QTableWidgetItem(info[i].in_time));
            this->ui->tableWidget->setItem(row,3,new QTableWidgetItem(info[i].out_time));
            this->ui->tableWidget->setItem(row,4,new QTableWidgetItem(QIcon(info[i].in_path),""));
            this->ui->tableWidget->setItem(row,5,new QTableWidgetItem(QIcon(info[i].out_path),""));
            this->ui->tableWidget->setItem(row,6,new QTableWidgetItem(Money));
        }

    }
    else if(flag ==0)
    {
        QMessageBox::information(this,"hint","no more data");
    }

}


//export excel
void CSearchWin::on_pushButton_2_clicked()
{

    QString filepath = "./ExportData";
    QString filename =filepath + "/" + shareinfo->getCurrenttime() +".csv";
    QFile file(filename);
    int row = this->ui->tableWidget->rowCount();
    //open
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
       qDebug()<<"file open field!" ;
    }
    //save head
    vector<QString> head;
    head.clear();
    head.push_back(ui->tableWidget->horizontalHeaderItem(0)->text());
    head.push_back(ui->tableWidget->horizontalHeaderItem(1)->text());
    head.push_back(ui->tableWidget->horizontalHeaderItem(2)->text());
    head.push_back(ui->tableWidget->horizontalHeaderItem(3)->text());
    head.push_back(ui->tableWidget->horizontalHeaderItem(4)->text());
    head.push_back(ui->tableWidget->horizontalHeaderItem(5)->text());
    head.push_back(ui->tableWidget->horizontalHeaderItem(6)->text());

    //wirte
    QTextStream out(&file);
    out<<head[0]<<","<<head[1]<<","<<head[2]<<","<<head[3]<<","<<head[4]<<","<<head[5]<<","<<head[6]<<","<<",\n";
    for(int i=0; i<this->vec_info.size(); i++)
    {
        out<<i<<","
           <<this->vec_info[i].plate<<","
             <<this->vec_info[i].in_time<<","
               <<this->vec_info[i].out_time<<","
                 <<this->vec_info[i].in_path<<","
                   <<this->vec_info[i].out_path<<","
                     <<this->vec_info[i].charge<<","
                    <<",\n";
    }

    //close
    file.close();
    QMessageBox::information(this,"hint","save data ok");
}

//search something
void CSearchWin::on_pushButton_clicked()
{
    //all edit is empty give hint
    if(this->ui->lineEdit->text().isEmpty() && this->ui->lineEdit_2->text().isEmpty() && this->ui->lineEdit_3->text().isEmpty())
    {
        QMessageBox::warning(this, "waarning!!","all editline is empty");
    }
    else //search some
    {
        this->page =0;
        //qDebug()<<this->ui->lineEdit_2->text(); //2022-07-26
        //qDebug()<<this->ui->lineEdit_3->text();
        memset(&this->csearch, 0, sizeof(this->csearch));
        memset(&this->head,0,sizeof(this->head));
        this->csearch.index = 0;
        memcpy(this->csearch.plate,this->ui->lineEdit->text().toStdString().c_str(), sizeof(this->csearch.plate));
        memcpy(this->csearch.in_time,this->ui->lineEdit_2->text().toStdString().c_str(),sizeof(this->csearch.in_time));
        memcpy(this->csearch.out_time,this->ui->lineEdit_3->text().toStdString().c_str(),sizeof(this->csearch.out_time));
        char res[1024]={0};
        memcpy(res,&this->csearch, sizeof(this->csearch));

        this->head.bussinesstype =21;
        this->head.CRC = shareinfo->CalcCRCCode((unsigned char*)res, sizeof(this->csearch));
        this->head.bussinesslen=sizeof(this->csearch);

        memset(buf,0,sizeof(this->buf));
        memcpy(buf,&this->head,sizeof(this->head));
        memcpy(buf + sizeof(head), &this->csearch, sizeof(this->csearch));

        this->wt->setData(buf, sizeof(this->head) + sizeof(this->csearch));
        qDebug()<<"send to server ok and type = 21";
    }
}

//more
void CSearchWin::on_pushButton_4_clicked()
{
    this->page++;
    memset(&this->csearch, 0, sizeof(this->csearch));
    memset(&this->head,0,sizeof(this->head));
    this->csearch.index = this->page;
    memcpy(this->csearch.plate,this->ui->lineEdit->text().toStdString().c_str(), sizeof(this->csearch.plate));
    memcpy(this->csearch.in_time,this->ui->lineEdit_2->text().toStdString().c_str(),sizeof(this->csearch.in_time));
    memcpy(this->csearch.out_time,this->ui->lineEdit_3->text().toStdString().c_str(),sizeof(this->csearch.out_time));
    char res[1024]={0};
    memcpy(res, &this->csearch, sizeof(this->csearch));

    this->head.bussinesstype =22;
    this->head.CRC = shareinfo->CalcCRCCode((unsigned char*)res,sizeof(this->csearch));
    this->head.bussinesslen=sizeof(this->csearch);

    memset(buf,0,sizeof(this->buf));
    memcpy(buf,&this->head,sizeof(this->head));
    memcpy(buf + sizeof(head), &this->csearch, sizeof(this->csearch));

    this->wt->setData(buf, sizeof(this->head) + sizeof(this->csearch));
    qDebug()<<"send to server ok and type = 22";
}
