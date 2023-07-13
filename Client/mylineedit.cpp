#include "mylineedit.h"

MyLineEdit::MyLineEdit(QWidget *parent):QLineEdit(parent)
{

}

//press leftbutton would send signals
void MyLineEdit::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        emit clicked();
    }
}
