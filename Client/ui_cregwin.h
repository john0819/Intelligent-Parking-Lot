/********************************************************************************
** Form generated from reading UI file 'cregwin.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREGWIN_H
#define UI_CREGWIN_H

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

class Ui_CRegWin
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QWidget *CRegWin)
    {
        if (CRegWin->objectName().isEmpty())
            CRegWin->setObjectName(QStringLiteral("CRegWin"));
        CRegWin->resize(829, 656);
        label = new QLabel(CRegWin);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(330, 20, 381, 71));
        label_2 = new QLabel(CRegWin);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(150, 140, 141, 51));
        lineEdit = new QLineEdit(CRegWin);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(300, 140, 261, 51));
        label_3 = new QLabel(CRegWin);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(140, 230, 141, 51));
        label_4 = new QLabel(CRegWin);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(140, 330, 141, 51));
        label_5 = new QLabel(CRegWin);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(110, 420, 141, 51));
        lineEdit_2 = new QLineEdit(CRegWin);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(300, 230, 261, 51));
        lineEdit_3 = new QLineEdit(CRegWin);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(300, 330, 261, 51));
        lineEdit_4 = new QLineEdit(CRegWin);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(300, 430, 261, 51));
        pushButton = new QPushButton(CRegWin);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(100, 550, 181, 51));
        pushButton_2 = new QPushButton(CRegWin);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(500, 550, 181, 51));
        pushButton_3 = new QPushButton(CRegWin);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(600, 330, 151, 51));

        retranslateUi(CRegWin);

        QMetaObject::connectSlotsByName(CRegWin);
    } // setupUi

    void retranslateUi(QWidget *CRegWin)
    {
        CRegWin->setWindowTitle(QApplication::translate("CRegWin", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("CRegWin", "User Registeration Window", Q_NULLPTR));
        label_2->setText(QApplication::translate("CRegWin", "Account", Q_NULLPTR));
        label_3->setText(QApplication::translate("CRegWin", "User Name", Q_NULLPTR));
        label_4->setText(QApplication::translate("CRegWin", "Password", Q_NULLPTR));
        label_5->setText(QApplication::translate("CRegWin", "Password Again", Q_NULLPTR));
        pushButton->setText(QApplication::translate("CRegWin", "YES", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("CRegWin", "CANCEL", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("CRegWin", "HIDE!!", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CRegWin: public Ui_CRegWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREGWIN_H
