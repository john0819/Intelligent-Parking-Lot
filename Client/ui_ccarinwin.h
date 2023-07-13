/********************************************************************************
** Form generated from reading UI file 'ccarinwin.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CCARINWIN_H
#define UI_CCARINWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CCarInWin
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QTableWidget *tableWidget;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QPushButton *pushButton_3;

    void setupUi(QWidget *CCarInWin)
    {
        if (CCarInWin->objectName().isEmpty())
            CCarInWin->setObjectName(QStringLiteral("CCarInWin"));
        CCarInWin->resize(1271, 727);
        label = new QLabel(CCarInWin);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 691, 581));
        label_2 = new QLabel(CCarInWin);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(770, 0, 171, 51));
        label_3 = new QLabel(CCarInWin);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(770, 160, 171, 51));
        label_4 = new QLabel(CCarInWin);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(770, 320, 171, 51));
        lineEdit = new QLineEdit(CCarInWin);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(770, 70, 361, 51));
        lineEdit_2 = new QLineEdit(CCarInWin);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(780, 390, 181, 51));
        pushButton = new QPushButton(CCarInWin);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(1000, 390, 141, 51));
        pushButton_2 = new QPushButton(CCarInWin);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(1000, 240, 141, 51));
        label_5 = new QLabel(CCarInWin);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(780, 230, 181, 61));
        label_6 = new QLabel(CCarInWin);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 670, 171, 51));
        label_7 = new QLabel(CCarInWin);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(360, 670, 171, 51));
        label_8 = new QLabel(CCarInWin);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(640, 660, 171, 51));
        tableWidget = new QTableWidget(CCarInWin);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(740, 470, 431, 171));
        lineEdit_3 = new QLineEdit(CCarInWin);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(180, 670, 131, 41));
        lineEdit_4 = new QLineEdit(CCarInWin);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(470, 670, 131, 41));
        lineEdit_5 = new QLineEdit(CCarInWin);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(760, 660, 241, 51));
        pushButton_3 = new QPushButton(CCarInWin);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(1190, 430, 61, 191));

        retranslateUi(CCarInWin);

        QMetaObject::connectSlotsByName(CCarInWin);
    } // setupUi

    void retranslateUi(QWidget *CCarInWin)
    {
        CCarInWin->setWindowTitle(QApplication::translate("CCarInWin", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("CCarInWin", "TextLabel", Q_NULLPTR));
        label_2->setText(QApplication::translate("CCarInWin", "Enter Parking Time:", Q_NULLPTR));
        label_3->setText(QApplication::translate("CCarInWin", "License Plate Picture:", Q_NULLPTR));
        label_4->setText(QApplication::translate("CCarInWin", "License Plate Number:", Q_NULLPTR));
        pushButton->setText(QApplication::translate("CCarInWin", "Modify", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("CCarInWin", "Take", Q_NULLPTR));
        label_5->setText(QApplication::translate("CCarInWin", "Picture", Q_NULLPTR));
        label_6->setText(QApplication::translate("CCarInWin", "The rest number of lot:", Q_NULLPTR));
        label_7->setText(QApplication::translate("CCarInWin", "Current user:", Q_NULLPTR));
        label_8->setText(QApplication::translate("CCarInWin", "System time:", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CCarInWin", "Num", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CCarInWin", "License Number", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("CCarInWin", "Time", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("CCarInWin", "Site", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("CCarInWin", "MORE", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CCarInWin: public Ui_CCarInWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CCARINWIN_H
