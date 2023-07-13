/********************************************************************************
** Form generated from reading UI file 'bigpicture.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BIGPICTURE_H
#define UI_BIGPICTURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BigPicture
{
public:
    QLabel *label;

    void setupUi(QWidget *BigPicture)
    {
        if (BigPicture->objectName().isEmpty())
            BigPicture->setObjectName(QStringLiteral("BigPicture"));
        BigPicture->resize(612, 475);
        label = new QLabel(BigPicture);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 0, 611, 471));

        retranslateUi(BigPicture);

        QMetaObject::connectSlotsByName(BigPicture);
    } // setupUi

    void retranslateUi(QWidget *BigPicture)
    {
        BigPicture->setWindowTitle(QApplication::translate("BigPicture", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("BigPicture", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BigPicture: public Ui_BigPicture {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BIGPICTURE_H
