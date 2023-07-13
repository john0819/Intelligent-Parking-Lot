/********************************************************************************
** Form generated from reading UI file 'csetwin.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CSETWIN_H
#define UI_CSETWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CSetWin
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QLabel *label_7;

    void setupUi(QWidget *CSetWin)
    {
        if (CSetWin->objectName().isEmpty())
            CSetWin->setObjectName(QStringLiteral("CSetWin"));
        CSetWin->resize(961, 793);
        label = new QLabel(CSetWin);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(310, 30, 381, 71));
        label_2 = new QLabel(CSetWin);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(100, 150, 181, 61));
        label_3 = new QLabel(CSetWin);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(100, 260, 181, 61));
        label_4 = new QLabel(CSetWin);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(100, 370, 181, 61));
        label_5 = new QLabel(CSetWin);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(100, 480, 181, 61));
        label_6 = new QLabel(CSetWin);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(100, 590, 181, 61));
        pushButton = new QPushButton(CSetWin);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(150, 700, 141, 51));
        pushButton_2 = new QPushButton(CSetWin);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(600, 700, 141, 51));
        lineEdit = new QLineEdit(CSetWin);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(320, 160, 301, 51));
        lineEdit_2 = new QLineEdit(CSetWin);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(320, 270, 301, 51));
        lineEdit_3 = new QLineEdit(CSetWin);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(320, 380, 301, 51));
        lineEdit_4 = new QLineEdit(CSetWin);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(320, 490, 301, 51));
        lineEdit_5 = new QLineEdit(CSetWin);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(320, 600, 151, 51));
        pushButton_3 = new QPushButton(CSetWin);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(650, 390, 121, 41));
        pushButton_4 = new QPushButton(CSetWin);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(650, 500, 121, 41));
        label_7 = new QLabel(CSetWin);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(510, 610, 91, 31));

        retranslateUi(CSetWin);

        QMetaObject::connectSlotsByName(CSetWin);
    } // setupUi

    void retranslateUi(QWidget *CSetWin)
    {
        CSetWin->setWindowTitle(QApplication::translate("CSetWin", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("CSetWin", "Intelligent Parking System Setting Interface", Q_NULLPTR));
        label_2->setText(QApplication::translate("CSetWin", "Server IP address:", Q_NULLPTR));
        label_3->setText(QApplication::translate("CSetWin", "Server Host address:", Q_NULLPTR));
        label_4->setText(QApplication::translate("CSetWin", "License saving address:", Q_NULLPTR));
        label_5->setText(QApplication::translate("CSetWin", "Video saving address:", Q_NULLPTR));
        label_6->setText(QApplication::translate("CSetWin", "Local system storage size:", Q_NULLPTR));
        pushButton->setText(QApplication::translate("CSetWin", "YES", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("CSetWin", "OUT", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("CSetWin", "Choose", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("CSetWin", "Choose", Q_NULLPTR));
        label_7->setText(QApplication::translate("CSetWin", "GB", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CSetWin: public Ui_CSetWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CSETWIN_H
