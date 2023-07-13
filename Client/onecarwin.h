#ifndef ONECARWIN_H
#define ONECARWIN_H

#include <QWidget>
#include "protocol.h"

namespace Ui {
class OneCarWin;
}

class OneCarWin : public QWidget
{
    Q_OBJECT

public:
    explicit OneCarWin(CARIN carin,QWidget *parent = nullptr);
    ~OneCarWin();

protected:
    bool eventFilter(QObject *obj, QEvent *e);


private:
    Ui::OneCarWin *ui;
};

#endif // ONECARWIN_H
