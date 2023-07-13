/********************************************************************************
** Form generated from reading UI file 'parkingvcrwin.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARKINGVCRWIN_H
#define UI_PARKINGVCRWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParkingVCRWin
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QCheckBox *checkBox;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;

    void setupUi(QWidget *ParkingVCRWin)
    {
        if (ParkingVCRWin->objectName().isEmpty())
            ParkingVCRWin->setObjectName(QStringLiteral("ParkingVCRWin"));
        ParkingVCRWin->resize(1268, 738);
        label = new QLabel(ParkingVCRWin);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 40, 391, 41));
        QFont font;
        font.setPointSize(15);
        label->setFont(font);
        label_2 = new QLabel(ParkingVCRWin);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 130, 611, 551));
        label_3 = new QLabel(ParkingVCRWin);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(760, 130, 391, 41));
        label_3->setFont(font);
        label_4 = new QLabel(ParkingVCRWin);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(810, 210, 251, 41));
        label_5 = new QLabel(ParkingVCRWin);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(810, 280, 251, 41));
        checkBox = new QCheckBox(ParkingVCRWin);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(760, 640, 501, 51));
        QFont font1;
        font1.setPointSize(14);
        checkBox->setFont(font1);
        pushButton = new QPushButton(ParkingVCRWin);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(800, 400, 341, 51));
        QFont font2;
        font2.setPointSize(13);
        pushButton->setFont(font2);
        pushButton_2 = new QPushButton(ParkingVCRWin);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(800, 540, 341, 51));
        pushButton_2->setFont(font2);
        lineEdit = new QLineEdit(ParkingVCRWin);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(1060, 210, 191, 41));
        lineEdit_2 = new QLineEdit(ParkingVCRWin);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(1060, 280, 191, 41));

        retranslateUi(ParkingVCRWin);

        QMetaObject::connectSlotsByName(ParkingVCRWin);
    } // setupUi

    void retranslateUi(QWidget *ParkingVCRWin)
    {
        ParkingVCRWin->setWindowTitle(QApplication::translate("ParkingVCRWin", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("ParkingVCRWin", "Parking lot real-time monitoring screen", Q_NULLPTR));
        label_2->setText(QApplication::translate("ParkingVCRWin", "TextLabel", Q_NULLPTR));
        label_3->setText(QApplication::translate("ParkingVCRWin", "Current car information (real-time)", Q_NULLPTR));
        label_4->setText(QApplication::translate("ParkingVCRWin", "The number of car in Parking lot", Q_NULLPTR));
        label_5->setText(QApplication::translate("ParkingVCRWin", "The number of spare Parking lot", Q_NULLPTR));
        checkBox->setText(QApplication::translate("ParkingVCRWin", "Video Monitor automatically recording (per 30)", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ParkingVCRWin", "Snapshot of vehicle features", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("ParkingVCRWin", "Parking Lot manually recoding", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ParkingVCRWin: public Ui_ParkingVCRWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARKINGVCRWIN_H
