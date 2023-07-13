/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QLabel *label;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QWidget *page_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1481, 1064);
        label = new QLabel(MainWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(90, 1010, 401, 51));
        QFont font;
        font.setPointSize(15);
        label->setFont(font);
        stackedWidget = new QStackedWidget(MainWindow);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(100, 120, 1321, 871));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        stackedWidget->addWidget(page_2);
        pushButton = new QPushButton(MainWindow);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(50, 30, 181, 51));
        QFont font1;
        font1.setPointSize(13);
        pushButton->setFont(font1);
        pushButton_2 = new QPushButton(MainWindow);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(290, 30, 181, 51));
        pushButton_2->setFont(font1);
        pushButton_3 = new QPushButton(MainWindow);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(530, 30, 181, 51));
        pushButton_3->setFont(font1);
        pushButton_4 = new QPushButton(MainWindow);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(780, 30, 181, 51));
        pushButton_4->setFont(font1);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Intelligent  Parking  Lot  Managing  System", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Leave Parking Lot", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "Internal Management", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "Information Search", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "System Setting", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
