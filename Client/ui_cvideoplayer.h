/********************************************************************************
** Form generated from reading UI file 'cvideoplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CVIDEOPLAYER_H
#define UI_CVIDEOPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CVideoPlayer
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QComboBox *comboBox;
    QSlider *horizontalSlider;

    void setupUi(QWidget *CVideoPlayer)
    {
        if (CVideoPlayer->objectName().isEmpty())
            CVideoPlayer->setObjectName(QStringLiteral("CVideoPlayer"));
        CVideoPlayer->resize(1229, 825);
        label = new QLabel(CVideoPlayer);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 1201, 601));
        label_2 = new QLabel(CVideoPlayer);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(40, 740, 131, 51));
        lineEdit = new QLineEdit(CVideoPlayer);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(180, 750, 131, 41));
        pushButton = new QPushButton(CVideoPlayer);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(490, 730, 181, 71));
        comboBox = new QComboBox(CVideoPlayer);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(810, 740, 111, 41));
        horizontalSlider = new QSlider(CVideoPlayer);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(90, 660, 971, 41));
        horizontalSlider->setOrientation(Qt::Horizontal);

        retranslateUi(CVideoPlayer);

        QMetaObject::connectSlotsByName(CVideoPlayer);
    } // setupUi

    void retranslateUi(QWidget *CVideoPlayer)
    {
        CVideoPlayer->setWindowTitle(QApplication::translate("CVideoPlayer", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("CVideoPlayer", "TextLabel", Q_NULLPTR));
        label_2->setText(QApplication::translate("CVideoPlayer", "Speed of Progress", Q_NULLPTR));
        pushButton->setText(QApplication::translate("CVideoPlayer", "Stop", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("CVideoPlayer", "x1.0", Q_NULLPTR)
         << QApplication::translate("CVideoPlayer", "x1.5", Q_NULLPTR)
         << QApplication::translate("CVideoPlayer", "x2.0", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class CVideoPlayer: public Ui_CVideoPlayer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CVIDEOPLAYER_H
