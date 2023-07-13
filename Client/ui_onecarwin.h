/********************************************************************************
** Form generated from reading UI file 'onecarwin.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONECARWIN_H
#define UI_ONECARWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OneCarWin
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_5;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLabel *label_6;
    QLineEdit *lineEdit_4;
    QLabel *label_4;

    void setupUi(QWidget *OneCarWin)
    {
        if (OneCarWin->objectName().isEmpty())
            OneCarWin->setObjectName(QStringLiteral("OneCarWin"));
        OneCarWin->resize(1405, 730);
        label = new QLabel(OneCarWin);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(780, 130, 591, 541));
        label_2 = new QLabel(OneCarWin);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(970, 30, 201, 31));
        QFont font;
        font.setPointSize(25);
        label_2->setFont(font);
        label_3 = new QLabel(OneCarWin);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 310, 201, 31));
        label_3->setFont(font);
        label_5 = new QLabel(OneCarWin);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(580, 310, 201, 31));
        label_5->setFont(font);
        lineEdit = new QLineEdit(OneCarWin);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(20, 410, 171, 81));
        lineEdit_2 = new QLineEdit(OneCarWin);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(260, 410, 241, 81));
        lineEdit_3 = new QLineEdit(OneCarWin);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(560, 410, 171, 81));
        label_6 = new QLabel(OneCarWin);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(300, 310, 201, 31));
        label_6->setFont(font);
        lineEdit_4 = new QLineEdit(OneCarWin);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(280, 150, 171, 81));
        label_4 = new QLabel(OneCarWin);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(320, 50, 201, 41));
        label_4->setFont(font);

        retranslateUi(OneCarWin);

        QMetaObject::connectSlotsByName(OneCarWin);
    } // setupUi

    void retranslateUi(QWidget *OneCarWin)
    {
        OneCarWin->setWindowTitle(QApplication::translate("OneCarWin", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("OneCarWin", "TextLabel", Q_NULLPTR));
        label_2->setText(QApplication::translate("OneCarWin", "Car Picture", Q_NULLPTR));
        label_3->setText(QApplication::translate("OneCarWin", "Car Plate", Q_NULLPTR));
        label_5->setText(QApplication::translate("OneCarWin", "Car Site", Q_NULLPTR));
        label_6->setText(QApplication::translate("OneCarWin", "Car Time", Q_NULLPTR));
        lineEdit_4->setText(QString());
        label_4->setText(QApplication::translate("OneCarWin", "Car ID", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OneCarWin: public Ui_OneCarWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONECARWIN_H
