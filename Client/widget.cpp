#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    mythread = new MyThread(); //create mythread to emit frame
    qRegisterMetaType<Mat>("Mat"); //register signal
    connect(this->mythread,SIGNAL(Send2Widget(Mat)),this,SLOT(GetFrame(Mat)));
    connect(this->mythread,SIGNAL(Sendchange()),this,SLOT(changeWin()));
    mythread->start(); //star open video

}

Widget::~Widget()
{
    delete ui;
}

//play video
void Widget::GetFrame(Mat frame)
{
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
    this->update();
}

void Widget::changeWin()
{
    this->setwin = new CSetWin();
    this->hide();
    this->setwin->show();
}
