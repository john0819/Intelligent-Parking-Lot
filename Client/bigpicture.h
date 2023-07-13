#ifndef BIGPICTURE_H
#define BIGPICTURE_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class BigPicture;
}

class BigPicture : public QWidget
{
    Q_OBJECT

public:
    BigPicture(QListWidgetItem *item, QRect rect, QWidget *parent = nullptr);
    ~BigPicture();

protected:
    bool eventFilter(QObject *obj, QEvent *e);

private:
    Ui::BigPicture *ui;
};

#endif // BIGPICTURE_H
