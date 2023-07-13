#include "onecarwin.h"
#include "ui_onecarwin.h"
#include <QImage>

OneCarWin::OneCarWin(CARIN carin,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OneCarWin)
{
    ui->setupUi(this);
    this->ui->lineEdit->setText(carin.plate);
    this->ui->lineEdit_2->setText(carin.time);
    this->ui->lineEdit_3->setText(carin.site);
    QString car_id = QString::number(carin.imageid, 10);
    this->ui->lineEdit_4->setText(car_id);
    //picture
    QImage image(carin.filepath);
    this->ui->label->setPixmap(QPixmap::fromImage(image));
    this->ui->label->resize(image.width(),image.height());

}

OneCarWin::~OneCarWin()
{
    delete ui;
}

bool OneCarWin::eventFilter(QObject *obj, QEvent *e)
{
    if(e->type() == QEvent::MouseButtonPress)
    {
        this->close();
    }
    return QWidget::eventFilter(obj, e);
}
