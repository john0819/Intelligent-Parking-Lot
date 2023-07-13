#include "bigpicture.h"
#include "ui_bigpicture.h"
#include <QDebug>

//show picture


BigPicture::BigPicture(QListWidgetItem *item, QRect rect, QWidget *parent):
    QWidget(parent),
    ui(new Ui::BigPicture)
{
    qDebug()<<"big?";
    this->installEventFilter(this);
    ui->setupUi(this);
    this->setGeometry(rect);//设置显示图片窗口的x、y、w、h
    this->setFixedSize(rect.width(), rect.height());//设置窗口固定大小
    this->setWindowIcon(item->icon());
    this->setWindowTitle("Big Picture");

    this->setWindowModality(Qt::ApplicationModal);
    this->ui->label->setFixedSize(this->width(), this->height());
    this->ui->label->setPixmap(item->icon().pixmap(QSize(this->width(), this->height())).scaled(this->ui->label->width(),this->ui->label->height()));

}

BigPicture::~BigPicture()
{
    delete ui;
}

//close big picture
bool BigPicture::eventFilter(QObject *obj, QEvent *e)
{
    if(e->type() == QEvent::MouseButtonPress)
    {
        this->close();
    }
    return QWidget::eventFilter(obj, e);
}
