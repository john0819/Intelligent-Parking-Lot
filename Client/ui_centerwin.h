/********************************************************************************
** Form generated from reading UI file 'centerwin.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CENTERWIN_H
#define UI_CENTERWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "verificationcodelabel.h"

QT_BEGIN_NAMESPACE

class Ui_CEnterWin
{
public:
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_3;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    VerificationCodeLabel *label_5;

    void setupUi(QWidget *CEnterWin)
    {
        if (CEnterWin->objectName().isEmpty())
            CEnterWin->setObjectName(QStringLiteral("CEnterWin"));
        CEnterWin->resize(929, 630);
        label_2 = new QLabel(CEnterWin);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(210, 140, 141, 51));
        lineEdit = new QLineEdit(CEnterWin);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(360, 140, 261, 51));
        lineEdit_3 = new QLineEdit(CEnterWin);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(360, 360, 181, 51));
        label = new QLabel(CEnterWin);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(320, 30, 381, 71));
        lineEdit_2 = new QLineEdit(CEnterWin);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(360, 250, 261, 51));
        label_3 = new QLabel(CEnterWin);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(210, 250, 141, 51));
        label_4 = new QLabel(CEnterWin);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(160, 360, 141, 51));
        pushButton = new QPushButton(CEnterWin);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(190, 500, 171, 51));
        pushButton_2 = new QPushButton(CEnterWin);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(550, 500, 171, 51));
        label_5 = new VerificationCodeLabel(CEnterWin);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(580, 350, 181, 71));

        retranslateUi(CEnterWin);

        QMetaObject::connectSlotsByName(CEnterWin);
    } // setupUi

    void retranslateUi(QWidget *CEnterWin)
    {
        CEnterWin->setWindowTitle(QApplication::translate("CEnterWin", "Form", Q_NULLPTR));
        label_2->setText(QApplication::translate("CEnterWin", "Account", Q_NULLPTR));
        label->setText(QApplication::translate("CEnterWin", "Intelligent Parking System Setting Interface", Q_NULLPTR));
        label_3->setText(QApplication::translate("CEnterWin", "Password", Q_NULLPTR));
        label_4->setText(QApplication::translate("CEnterWin", "Verification Code", Q_NULLPTR));
        pushButton->setText(QApplication::translate("CEnterWin", "ENTER", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("CEnterWin", "REGISTER", Q_NULLPTR));
        label_5->setText(QApplication::translate("CEnterWin", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CEnterWin: public Ui_CEnterWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CENTERWIN_H
