/********************************************************************************
** Form generated from reading UI file 'vcrreviewwin.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VCRREVIEWWIN_H
#define UI_VCRREVIEWWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VCRReviewWin
{
public:
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QListWidget *listWidget;
    QListWidget *listWidget_2;
    QLabel *label;
    QPushButton *pushButton_2;

    void setupUi(QWidget *VCRReviewWin)
    {
        if (VCRReviewWin->objectName().isEmpty())
            VCRReviewWin->setObjectName(QStringLiteral("VCRReviewWin"));
        VCRReviewWin->resize(1147, 795);
        radioButton = new QRadioButton(VCRReviewWin);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(20, 70, 171, 51));
        radioButton_2 = new QRadioButton(VCRReviewWin);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(180, 70, 171, 51));
        listWidget = new QListWidget(VCRReviewWin);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(350, 100, 741, 561));
        listWidget_2 = new QListWidget(VCRReviewWin);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        listWidget_2->setGeometry(QRect(50, 200, 256, 541));
        label = new QLabel(VCRReviewWin);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 130, 181, 51));
        QFont font;
        font.setPointSize(15);
        label->setFont(font);
        pushButton_2 = new QPushButton(VCRReviewWin);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(360, 680, 151, 51));
        pushButton_2->setFont(font);

        retranslateUi(VCRReviewWin);

        QMetaObject::connectSlotsByName(VCRReviewWin);
    } // setupUi

    void retranslateUi(QWidget *VCRReviewWin)
    {
        VCRReviewWin->setWindowTitle(QApplication::translate("VCRReviewWin", "Form", Q_NULLPTR));
        radioButton->setText(QApplication::translate("VCRReviewWin", "Base on Month", Q_NULLPTR));
        radioButton_2->setText(QApplication::translate("VCRReviewWin", "Base on Day", Q_NULLPTR));
        label->setText(QApplication::translate("VCRReviewWin", "Search Menu", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("VCRReviewWin", "MORE", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VCRReviewWin: public Ui_VCRReviewWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VCRREVIEWWIN_H
