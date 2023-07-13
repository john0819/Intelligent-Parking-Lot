/********************************************************************************
** Form generated from reading UI file 'csearchwin.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CSEARCHWIN_H
#define UI_CSEARCHWIN_H

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
#include "mylineedit.h"

QT_BEGIN_NAMESPACE

class Ui_CSearchWin
{
public:
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit;
    MyLineEdit *lineEdit_2;
    MyLineEdit *lineEdit_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTableWidget *tableWidget;

    void setupUi(QWidget *CSearchWin)
    {
        if (CSearchWin->objectName().isEmpty())
            CSearchWin->setObjectName(QStringLiteral("CSearchWin"));
        CSearchWin->resize(1377, 790);
        label = new QLabel(CSearchWin);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 60, 161, 71));
        label_3 = new QLabel(CSearchWin);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(920, 60, 171, 71));
        label_4 = new QLabel(CSearchWin);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(450, 60, 201, 71));
        lineEdit = new QLineEdit(CSearchWin);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(230, 70, 141, 51));
        lineEdit_2 = new MyLineEdit(CSearchWin);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(620, 70, 211, 51));
        lineEdit_3 = new MyLineEdit(CSearchWin);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(1100, 70, 201, 51));
        pushButton = new QPushButton(CSearchWin);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(60, 690, 121, 51));
        pushButton_2 = new QPushButton(CSearchWin);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(1030, 680, 171, 61));
        tableWidget = new QTableWidget(CSearchWin);
        if (tableWidget->columnCount() < 7)
            tableWidget->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(50, 170, 1251, 481));

        retranslateUi(CSearchWin);

        QMetaObject::connectSlotsByName(CSearchWin);
    } // setupUi

    void retranslateUi(QWidget *CSearchWin)
    {
        CSearchWin->setWindowTitle(QApplication::translate("CSearchWin", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("CSearchWin", "License Plate Number:", Q_NULLPTR));
        label_3->setText(QApplication::translate("CSearchWin", "Leave Parking Lot Time:", Q_NULLPTR));
        label_4->setText(QApplication::translate("CSearchWin", "Enter Parking Lot Time:", Q_NULLPTR));
        pushButton->setText(QApplication::translate("CSearchWin", "Search", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("CSearchWin", "Export Excel", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CSearchWin", "Num", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CSearchWin", "License", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("CSearchWin", "Enter Time", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("CSearchWin", "Leave Time", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("CSearchWin", "Enter Picture", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("CSearchWin", "Leave Picture", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("CSearchWin", "Paarking Price", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CSearchWin: public Ui_CSearchWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CSEARCHWIN_H
