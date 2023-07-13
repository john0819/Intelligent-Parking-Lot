#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csetwin.h"

MainWindow * MainWindow::main =nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //manager window
    this->manager = CManageWin::getInstance();
//    this->setwin = new CSetWin();
    //init
    this->rt = ReadThread::getInstance();
    this->wt = WriteThread::getInstance();
    memset(&this->head,0,sizeof(this->head));
    this->shareinfo = ShareInfo::getInstance();

    //init some
    this->ui->stackedWidget->insertWidget(0,manager->carinwin());
    this->ui->stackedWidget->insertWidget(1,manager->vcrwin());
    this->ui->stackedWidget->insertWidget(2,manager->searchwin());
//    this->ui->stackedWidget->insertWidget(3,this->setwin);
    this->ui->stackedWidget->insertWidget(4,manager->caroutwin());
    this->ui->stackedWidget->insertWidget(5,manager->reviewwin());

    //btn connect window
    this->ui->pushButton->setObjectName("Leave Parking Lot");
    this->ui->pushButton_2->setObjectName("Internal Management");
    this->ui->pushButton_3->setObjectName("Information Search");
    this->ui->pushButton_4->setObjectName("System Setting");
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(ChangeWidgetSlot()));
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(ChangeWidgetSlot()));
    connect(ui->pushButton_3,SIGNAL(clicked()),this,SLOT(ChangeWidgetSlot()));
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(ChangeWidgetSlot()));

    //set current : car in
    this->ui->stackedWidget->setCurrentIndex(0);

}

MainWindow *MainWindow::getInstence()
{
    if(MainWindow::main == nullptr)
    {
        MainWindow::main = new MainWindow();
    }
    return MainWindow::main;
}

MainWindow::~MainWindow()
{
    delete ui;
}

//change QstackWidget content -> show different window
void MainWindow::ChangeWidgetSlot()
{
    qDebug()<<"111";
    QPushButton *btn=qobject_cast<QPushButton*>(sender());
    if(btn->objectName() == "Leave Parking Lot")
    {
        ui->stackedWidget->setCurrentIndex(4); //car out
        manager->caroutwin()->StartThread(); //go thread
        this->ui->pushButton->setText("Enter Parking Lot");
        this->ui->pushButton->setObjectName("Enter Parking Lot");

    }
    else if(btn->objectName() == "Enter Parking Lot") //car in
    {
        ui->stackedWidget->setCurrentIndex(0);
        this->ui->pushButton->setText("Leave Parking Lot");
        this->ui->pushButton->setObjectName("Leave Parking Lot");

        //send server (type =3) only head
        char res[1024]={0};

        memset(&this->head,0,sizeof(this->head));
        this->head.bussinesstype=3;
        this->head.CRC=shareinfo->CalcCRCCode((unsigned char*)res, 0);
        this->head.bussinesslen=0;
        memset(this->buf,0,sizeof(this->buf));
        memcpy(this->buf,&(this->head),sizeof(this->head));
        this->wt->setData(buf,sizeof(this->head));
        qDebug()<<"send server ok, type =3";

    }
    else if(btn->objectName() == "Internal Management")
    {
        ui->stackedWidget->setCurrentIndex(1);
        qDebug()<<"vcrwin()->StartThread()";
        manager->vcrwin()->StartThread(); //go thread
        this->ui->pushButton_2->setText("Review Picture");
        this->ui->pushButton_2->setObjectName("Review Picture");

        //send server (type =10) only head
        char res[1024]={0};

        memset(&this->head,0,sizeof(this->head));
        this->head.bussinesstype=10;
        this->head.CRC=shareinfo->CalcCRCCode((unsigned char*)res, 0);
        this->head.bussinesslen=0;
        memset(this->buf,0,sizeof(this->buf));
        memcpy(this->buf,&(this->head),sizeof(this->head));
        this->wt->setData(buf,sizeof(this->head));
        qDebug()<<"send server ok, type =10";

    }
    else if(btn->objectName() == "Information Search")
    {
        ui->stackedWidget->setCurrentIndex(2);
    }
    else if(btn->objectName() == "System Setting")
    {
        this->setwin = new CSetWin();
//        this->setwin->show();
//        this->ui->stackedWidget->insertWidget(3,this->setwin);
//        ui->stackedWidget->setCurrentIndex(3);
        this->ui->stackedWidget->insertWidget(0,manager->carinwin());
        this->ui->stackedWidget->insertWidget(1,manager->vcrwin());
        this->ui->stackedWidget->insertWidget(2,manager->searchwin());
        this->ui->stackedWidget->insertWidget(3,this->setwin);
        this->ui->stackedWidget->insertWidget(4,manager->caroutwin());
        this->ui->stackedWidget->insertWidget(5,manager->reviewwin());
        ui->stackedWidget->setCurrentIndex(3);

    }
    else if(btn->objectName() == "Review Picture")
    {
        ui->stackedWidget->setCurrentIndex(5);
        this->ui->pushButton_2->setText("Internal Management");
        this->ui->pushButton_2->setObjectName("Internal Management");

        //send to server type =12
        char res[1024]={0};

        memset(&this->head,0,sizeof(this->head));
        this->head.bussinesstype = 12;
        this->head.bussinesslen = 0;
        this->head.CRC = shareinfo->CalcCRCCode((unsigned char*)res, 0);;
        memset(this->buf,0,sizeof(this->buf));
        memcpy(this->buf,&(this->head),sizeof(this->head));
        this->wt->setData(this->buf,sizeof(this->head));
        qDebug()<<"write server ok, type ==12";
    }
}
