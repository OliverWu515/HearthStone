/********************************************************************************
** Form generated from reading UI file 'choose.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSE_H
#define UI_CHOOSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mylabel.h"

QT_BEGIN_NAMESPACE

class Ui_choose
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTabWidget *herotab;
    QWidget *specified;
    QGridLayout *gridLayout_2;
    QStackedWidget *stackedWidget;
    QLabel *pagenum;
    QPushButton *nextpage;
    QPushButton *lastpage;
    QWidget *neutral;
    QGridLayout *gridLayout_3;
    QPushButton *lastpage_2;
    QStackedWidget *stackedWidget_2;
    QPushButton *nextpage_2;
    QLabel *pagenum_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QPushButton *returntolast;
    QListWidget *cardsinf;
    QVBoxLayout *verticalLayout;
    mylabel *promptcard;
    QLabel *hint;
    QPushButton *deletebutton;

    void setupUi(QMainWindow *choose)
    {
        if (choose->objectName().isEmpty())
            choose->setObjectName("choose");
        choose->resize(1013, 439);
        centralwidget = new QWidget(choose);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        herotab = new QTabWidget(centralwidget);
        herotab->setObjectName("herotab");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(herotab->sizePolicy().hasHeightForWidth());
        herotab->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(12);
        herotab->setFont(font);
        specified = new QWidget();
        specified->setObjectName("specified");
        gridLayout_2 = new QGridLayout(specified);
        gridLayout_2->setObjectName("gridLayout_2");
        stackedWidget = new QStackedWidget(specified);
        stackedWidget->setObjectName("stackedWidget");

        gridLayout_2->addWidget(stackedWidget, 0, 1, 3, 1);

        pagenum = new QLabel(specified);
        pagenum->setObjectName("pagenum");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pagenum->sizePolicy().hasHeightForWidth());
        pagenum->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Times New Roman")});
        font1.setPointSize(10);
        pagenum->setFont(font1);

        gridLayout_2->addWidget(pagenum, 2, 3, 1, 1);

        nextpage = new QPushButton(specified);
        nextpage->setObjectName("nextpage");
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(nextpage->sizePolicy().hasHeightForWidth());
        nextpage->setSizePolicy(sizePolicy2);
        QFont font2;
        font2.setPointSize(16);
        nextpage->setFont(font2);

        gridLayout_2->addWidget(nextpage, 0, 3, 1, 1);

        lastpage = new QPushButton(specified);
        lastpage->setObjectName("lastpage");
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lastpage->sizePolicy().hasHeightForWidth());
        lastpage->setSizePolicy(sizePolicy3);
        lastpage->setFont(font2);

        gridLayout_2->addWidget(lastpage, 0, 0, 1, 1);

        herotab->addTab(specified, QString());
        neutral = new QWidget();
        neutral->setObjectName("neutral");
        gridLayout_3 = new QGridLayout(neutral);
        gridLayout_3->setObjectName("gridLayout_3");
        lastpage_2 = new QPushButton(neutral);
        lastpage_2->setObjectName("lastpage_2");
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(lastpage_2->sizePolicy().hasHeightForWidth());
        lastpage_2->setSizePolicy(sizePolicy4);
        lastpage_2->setFont(font2);

        gridLayout_3->addWidget(lastpage_2, 0, 0, 1, 1);

        stackedWidget_2 = new QStackedWidget(neutral);
        stackedWidget_2->setObjectName("stackedWidget_2");

        gridLayout_3->addWidget(stackedWidget_2, 0, 1, 2, 1);

        nextpage_2 = new QPushButton(neutral);
        nextpage_2->setObjectName("nextpage_2");
        sizePolicy4.setHeightForWidth(nextpage_2->sizePolicy().hasHeightForWidth());
        nextpage_2->setSizePolicy(sizePolicy4);
        nextpage_2->setFont(font2);

        gridLayout_3->addWidget(nextpage_2, 0, 2, 1, 1);

        pagenum_2 = new QLabel(neutral);
        pagenum_2->setObjectName("pagenum_2");
        sizePolicy1.setHeightForWidth(pagenum_2->sizePolicy().hasHeightForWidth());
        pagenum_2->setSizePolicy(sizePolicy1);
        pagenum_2->setFont(font1);

        gridLayout_3->addWidget(pagenum_2, 1, 2, 1, 1);

        herotab->addTab(neutral, QString());

        gridLayout->addWidget(herotab, 0, 0, 4, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setFont(font);

        horizontalLayout->addWidget(label);

        returntolast = new QPushButton(widget);
        returntolast->setObjectName("returntolast");
        returntolast->setFont(font);

        horizontalLayout->addWidget(returntolast);


        gridLayout->addWidget(widget, 3, 2, 1, 2);

        cardsinf = new QListWidget(centralwidget);
        cardsinf->setObjectName("cardsinf");
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(cardsinf->sizePolicy().hasHeightForWidth());
        cardsinf->setSizePolicy(sizePolicy5);

        gridLayout->addWidget(cardsinf, 1, 2, 1, 2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        promptcard = new mylabel(centralwidget);
        promptcard->setObjectName("promptcard");
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(promptcard->sizePolicy().hasHeightForWidth());
        promptcard->setSizePolicy(sizePolicy6);
        promptcard->setMinimumSize(QSize(0, 50));
        promptcard->setFrameShape(QFrame::Panel);
        promptcard->setFrameShadow(QFrame::Sunken);
        promptcard->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(promptcard);

        hint = new QLabel(centralwidget);
        hint->setObjectName("hint");
        QFont font3;
        font3.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font3.setPointSize(12);
        hint->setFont(font3);
        hint->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(hint);

        deletebutton = new QPushButton(centralwidget);
        deletebutton->setObjectName("deletebutton");
        QSizePolicy sizePolicy7(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(deletebutton->sizePolicy().hasHeightForWidth());
        deletebutton->setSizePolicy(sizePolicy7);
        deletebutton->setFont(font);

        verticalLayout->addWidget(deletebutton);


        gridLayout->addLayout(verticalLayout, 0, 2, 1, 2);

        choose->setCentralWidget(centralwidget);

        retranslateUi(choose);

        herotab->setCurrentIndex(0);
        stackedWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(choose);
    } // setupUi

    void retranslateUi(QMainWindow *choose)
    {
        choose->setWindowTitle(QCoreApplication::translate("choose", "MainWindow", nullptr));
        pagenum->setText(QCoreApplication::translate("choose", "num", nullptr));
        nextpage->setText(QString());
        lastpage->setText(QString());
        herotab->setTabText(herotab->indexOf(specified), QCoreApplication::translate("choose", "Tab 1", nullptr));
        lastpage_2->setText(QString());
        nextpage_2->setText(QString());
        pagenum_2->setText(QCoreApplication::translate("choose", "num", nullptr));
        herotab->setTabText(herotab->indexOf(neutral), QCoreApplication::translate("choose", "\351\200\232\347\224\250/ \344\270\255\347\253\213", nullptr));
        label->setText(QCoreApplication::translate("choose", "TextLabel", nullptr));
        returntolast->setText(QCoreApplication::translate("choose", " \350\277\224\345\233\236\344\270\212\347\272\247\350\217\234\345\215\225", nullptr));
        promptcard->setText(QCoreApplication::translate("choose", "newdeck", nullptr));
        hint->setText(QCoreApplication::translate("choose", "\346\217\220\347\244\272\357\274\232\347\202\271\345\207\273\344\270\212\351\235\242\347\232\204\346\241\206\345\217\257\344\273\245\344\277\256\346\224\271\345\215\241\347\273\204\345\220\215", nullptr));
        deletebutton->setText(QCoreApplication::translate("choose", "delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class choose: public Ui_choose {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSE_H
