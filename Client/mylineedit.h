#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H
#include <QLineEdit>
#include<QMouseEvent>

//this is lineedit which can send signals
class MyLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit MyLineEdit(QWidget *parent = 0);

protected:
    virtual void mousePressEvent(QMouseEvent *e); //mouse event

signals:
    void clicked();
};

#endif // MYLINEEDIT_H
