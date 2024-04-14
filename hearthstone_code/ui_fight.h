/********************************************************************************
** Form generated from reading UI file 'fight.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIGHT_H
#define UI_FIGHT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mylabel.h"

QT_BEGIN_NAMESPACE

class Ui_fight
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    mylabel *mytec;
    QLabel *information;
    QFrame *rivalboard;
    mylabel *myherolbl;
    QLabel *rivalcard;
    QPushButton *lose;
    QLabel *rivalcrystal;
    QPushButton *endrnd;
    QProgressBar *timebar;
    QLabel *weaponlbl;
    mylabel *rivalherolbl;
    QFrame *myboard;
    QLabel *mycrystal;
    QLabel *myname;
    QLabel *myherobld;
    QFrame *mycard;
    QLabel *rivalherobld;
    mylabel *rivaltec;
    QLabel *rivalweaponlbl;
    QLabel *rivalnamelbl;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *prompttext;
    QLabel *promptlabel;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *fight)
    {
        if (fight->objectName().isEmpty())
            fight->setObjectName("fight");
        fight->resize(1032, 642);
        centralwidget = new QWidget(fight);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        mytec = new mylabel(centralwidget);
        mytec->setObjectName("mytec");

        gridLayout->addWidget(mytec, 8, 1, 1, 1);

        information = new QLabel(centralwidget);
        information->setObjectName("information");
        QFont font;
        font.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font.setPointSize(12);
        information->setFont(font);
        information->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        gridLayout->addWidget(information, 1, 3, 1, 1);

        rivalboard = new QFrame(centralwidget);
        rivalboard->setObjectName("rivalboard");
        rivalboard->setFrameShape(QFrame::NoFrame);
        rivalboard->setFrameShadow(QFrame::Plain);

        gridLayout->addWidget(rivalboard, 2, 0, 1, 6);

        myherolbl = new mylabel(centralwidget);
        myherolbl->setObjectName("myherolbl");

        gridLayout->addWidget(myherolbl, 8, 0, 1, 1);

        rivalcard = new QLabel(centralwidget);
        rivalcard->setObjectName("rivalcard");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223")});
        font1.setPointSize(12);
        rivalcard->setFont(font1);

        gridLayout->addWidget(rivalcard, 1, 2, 1, 1);

        lose = new QPushButton(centralwidget);
        lose->setObjectName("lose");
        QFont font2;
        font2.setPointSize(12);
        lose->setFont(font2);

        gridLayout->addWidget(lose, 9, 5, 1, 1);

        rivalcrystal = new QLabel(centralwidget);
        rivalcrystal->setObjectName("rivalcrystal");
        rivalcrystal->setFont(font2);

        gridLayout->addWidget(rivalcrystal, 0, 4, 1, 1);

        endrnd = new QPushButton(centralwidget);
        endrnd->setObjectName("endrnd");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(endrnd->sizePolicy().hasHeightForWidth());
        endrnd->setSizePolicy(sizePolicy);
        endrnd->setFont(font2);

        gridLayout->addWidget(endrnd, 3, 5, 1, 1);

        timebar = new QProgressBar(centralwidget);
        timebar->setObjectName("timebar");
        timebar->setValue(100);
        timebar->setTextVisible(true);

        gridLayout->addWidget(timebar, 3, 0, 1, 5);

        weaponlbl = new QLabel(centralwidget);
        weaponlbl->setObjectName("weaponlbl");
        weaponlbl->setFont(font2);

        gridLayout->addWidget(weaponlbl, 9, 1, 1, 1);

        rivalherolbl = new mylabel(centralwidget);
        rivalherolbl->setObjectName("rivalherolbl");

        gridLayout->addWidget(rivalherolbl, 1, 0, 1, 1);

        myboard = new QFrame(centralwidget);
        myboard->setObjectName("myboard");
        myboard->setFrameShape(QFrame::NoFrame);
        myboard->setFrameShadow(QFrame::Plain);
        myboard->setLineWidth(0);

        gridLayout->addWidget(myboard, 7, 0, 1, 6);

        mycrystal = new QLabel(centralwidget);
        mycrystal->setObjectName("mycrystal");
        mycrystal->setFont(font2);

        gridLayout->addWidget(mycrystal, 9, 4, 1, 1);

        myname = new QLabel(centralwidget);
        myname->setObjectName("myname");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(myname->sizePolicy().hasHeightForWidth());
        myname->setSizePolicy(sizePolicy1);
        myname->setFont(font2);

        gridLayout->addWidget(myname, 9, 2, 1, 2);

        myherobld = new QLabel(centralwidget);
        myherobld->setObjectName("myherobld");
        myherobld->setFont(font2);

        gridLayout->addWidget(myherobld, 9, 0, 1, 1);

        mycard = new QFrame(centralwidget);
        mycard->setObjectName("mycard");
        mycard->setFrameShape(QFrame::NoFrame);
        mycard->setFrameShadow(QFrame::Plain);
        mycard->setLineWidth(0);

        gridLayout->addWidget(mycard, 8, 2, 1, 4);

        rivalherobld = new QLabel(centralwidget);
        rivalherobld->setObjectName("rivalherobld");
        rivalherobld->setFont(font2);

        gridLayout->addWidget(rivalherobld, 0, 0, 1, 1);

        rivaltec = new mylabel(centralwidget);
        rivaltec->setObjectName("rivaltec");

        gridLayout->addWidget(rivaltec, 1, 1, 1, 1);

        rivalweaponlbl = new QLabel(centralwidget);
        rivalweaponlbl->setObjectName("rivalweaponlbl");
        rivalweaponlbl->setFont(font2);

        gridLayout->addWidget(rivalweaponlbl, 0, 1, 1, 1);

        rivalnamelbl = new QLabel(centralwidget);
        rivalnamelbl->setObjectName("rivalnamelbl");
        sizePolicy1.setHeightForWidth(rivalnamelbl->sizePolicy().hasHeightForWidth());
        rivalnamelbl->setSizePolicy(sizePolicy1);
        rivalnamelbl->setFont(font2);

        gridLayout->addWidget(rivalnamelbl, 0, 2, 1, 2);

        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy2);
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        prompttext = new QLabel(widget);
        prompttext->setObjectName("prompttext");
        sizePolicy1.setHeightForWidth(prompttext->sizePolicy().hasHeightForWidth());
        prompttext->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(prompttext);

        promptlabel = new QLabel(widget);
        promptlabel->setObjectName("promptlabel");
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(promptlabel->sizePolicy().hasHeightForWidth());
        promptlabel->setSizePolicy(sizePolicy3);
        promptlabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        verticalLayout->addWidget(promptlabel);


        gridLayout->addWidget(widget, 1, 4, 1, 2);

        fight->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(fight);
        statusbar->setObjectName("statusbar");
        fight->setStatusBar(statusbar);

        retranslateUi(fight);

        QMetaObject::connectSlotsByName(fight);
    } // setupUi

    void retranslateUi(QMainWindow *fight)
    {
        fight->setWindowTitle(QCoreApplication::translate("fight", "MainWindow", nullptr));
        mytec->setText(QString());
        information->setText(QString());
        myherolbl->setText(QString());
        rivalcard->setText(QString());
        lose->setText(QCoreApplication::translate("fight", "\350\256\244\350\276\223", nullptr));
        rivalcrystal->setText(QString());
        endrnd->setText(QCoreApplication::translate("fight", "\345\233\236\345\220\210\345\210\207\346\215\242", nullptr));
        timebar->setFormat(QCoreApplication::translate("fight", "%v", nullptr));
        weaponlbl->setText(QString());
        rivalherolbl->setText(QString());
        mycrystal->setText(QString());
        myname->setText(QString());
        myherobld->setText(QString());
        rivalherobld->setText(QString());
        rivaltec->setText(QString());
        rivalweaponlbl->setText(QString());
        rivalnamelbl->setText(QString());
        prompttext->setText(QString());
        promptlabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class fight: public Ui_fight {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIGHT_H
