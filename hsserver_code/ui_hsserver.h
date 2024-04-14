/********************************************************************************
** Form generated from reading UI file 'hsserver.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HSSERVER_H
#define UI_HSSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HsServer
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTextBrowser *status;
    QTableWidget *userstate;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *portLE;
    QPushButton *startserver;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *HsServer)
    {
        if (HsServer->objectName().isEmpty())
            HsServer->setObjectName("HsServer");
        HsServer->resize(843, 650);
        centralwidget = new QWidget(HsServer);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        status = new QTextBrowser(centralwidget);
        status->setObjectName("status");

        gridLayout->addWidget(status, 0, 0, 1, 1);

        userstate = new QTableWidget(centralwidget);
        if (userstate->columnCount() < 2)
            userstate->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        userstate->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        userstate->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        userstate->setObjectName("userstate");

        gridLayout->addWidget(userstate, 0, 1, 1, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(widget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        portLE = new QLineEdit(widget);
        portLE->setObjectName("portLE");

        verticalLayout->addWidget(portLE);


        gridLayout->addWidget(widget, 2, 0, 2, 1);

        startserver = new QPushButton(centralwidget);
        startserver->setObjectName("startserver");

        gridLayout->addWidget(startserver, 2, 1, 2, 1);

        HsServer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(HsServer);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 843, 26));
        HsServer->setMenuBar(menubar);
        statusbar = new QStatusBar(HsServer);
        statusbar->setObjectName("statusbar");
        HsServer->setStatusBar(statusbar);

        retranslateUi(HsServer);

        QMetaObject::connectSlotsByName(HsServer);
    } // setupUi

    void retranslateUi(QMainWindow *HsServer)
    {
        HsServer->setWindowTitle(QCoreApplication::translate("HsServer", "HsServer", nullptr));
        QTableWidgetItem *___qtablewidgetitem = userstate->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("HsServer", "\345\205\210\346\211\213\350\200\205", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = userstate->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("HsServer", "\345\220\216\346\211\213\350\200\205", nullptr));
        label->setText(QCoreApplication::translate("HsServer", "\347\253\257\345\217\243\345\217\267\357\274\232\357\274\210\350\257\267\350\276\223\345\205\2458500-8600\344\271\213\351\227\264\347\232\204\346\225\260\357\274\211", nullptr));
        startserver->setText(QCoreApplication::translate("HsServer", "\345\220\257\345\212\250\346\234\215\345\212\241\345\231\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HsServer: public Ui_HsServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HSSERVER_H
