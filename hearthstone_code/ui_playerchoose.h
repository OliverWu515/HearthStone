/********************************************************************************
** Form generated from reading UI file 'playerchoose.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYERCHOOSE_H
#define UI_PLAYERCHOOSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mylabel.h"

QT_BEGIN_NAMESPACE

class Ui_playerchoose
{
public:
    QGridLayout *gridLayout;
    QFrame *player1frame;
    QVBoxLayout *verticalLayout;
    mylabel *player1;
    QLabel *hint;
    QLabel *player1inf;
    QTextBrowser *textBrowser;
    QPushButton *player1select;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QListWidget *deckinf;
    QPushButton *playerchooseexit;
    QFrame *line;
    QWidget *funcwidget;
    QGridLayout *gridLayout_2;
    QLineEdit *IPLE;
    QLabel *label_2;
    QLineEdit *PORTLE;
    QLabel *label;
    QLabel *displaylbl;
    QPushButton *connectbtn;
    QPushButton *startgame;

    void setupUi(QWidget *playerchoose)
    {
        if (playerchoose->objectName().isEmpty())
            playerchoose->setObjectName("playerchoose");
        playerchoose->resize(976, 709);
        gridLayout = new QGridLayout(playerchoose);
        gridLayout->setObjectName("gridLayout");
        player1frame = new QFrame(playerchoose);
        player1frame->setObjectName("player1frame");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(player1frame->sizePolicy().hasHeightForWidth());
        player1frame->setSizePolicy(sizePolicy);
        player1frame->setFrameShape(QFrame::Box);
        player1frame->setFrameShadow(QFrame::Raised);
        player1frame->setLineWidth(2);
        verticalLayout = new QVBoxLayout(player1frame);
        verticalLayout->setObjectName("verticalLayout");
        player1 = new mylabel(player1frame);
        player1->setObjectName("player1");
        sizePolicy.setHeightForWidth(player1->sizePolicy().hasHeightForWidth());
        player1->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223")});
        font.setPointSize(20);
        player1->setFont(font);
        player1->setFrameShape(QFrame::Panel);
        player1->setFrameShadow(QFrame::Sunken);
        player1->setAlignment(Qt::AlignCenter);
        player1->setMargin(0);

        verticalLayout->addWidget(player1);

        hint = new QLabel(player1frame);
        hint->setObjectName("hint");
        sizePolicy.setHeightForWidth(hint->sizePolicy().hasHeightForWidth());
        hint->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223")});
        font1.setPointSize(14);
        hint->setFont(font1);
        hint->setFrameShadow(QFrame::Plain);
        hint->setLineWidth(0);
        hint->setAlignment(Qt::AlignCenter);
        hint->setWordWrap(true);

        verticalLayout->addWidget(hint);

        player1inf = new QLabel(player1frame);
        player1inf->setObjectName("player1inf");
        sizePolicy.setHeightForWidth(player1inf->sizePolicy().hasHeightForWidth());
        player1inf->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setPointSize(18);
        player1inf->setFont(font2);
        player1inf->setLineWidth(0);
        player1inf->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        player1inf->setWordWrap(true);

        verticalLayout->addWidget(player1inf);

        textBrowser = new QTextBrowser(player1frame);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setFrameShape(QFrame::Panel);
        textBrowser->setLineWidth(6);

        verticalLayout->addWidget(textBrowser);

        player1select = new QPushButton(player1frame);
        player1select->setObjectName("player1select");
        player1select->setFont(font2);

        verticalLayout->addWidget(player1select);


        gridLayout->addWidget(player1frame, 0, 0, 1, 1);

        widget = new QWidget(playerchoose);
        widget->setObjectName("widget");
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        QFont font3;
        font3.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font3.setPointSize(14);
        label_3->setFont(font3);
        label_3->setLineWidth(0);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_3);

        deckinf = new QListWidget(widget);
        deckinf->setObjectName("deckinf");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(deckinf->sizePolicy().hasHeightForWidth());
        deckinf->setSizePolicy(sizePolicy1);
        deckinf->setFrameShape(QFrame::Panel);
        deckinf->setLineWidth(6);

        verticalLayout_2->addWidget(deckinf);

        playerchooseexit = new QPushButton(widget);
        playerchooseexit->setObjectName("playerchooseexit");
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(playerchooseexit->sizePolicy().hasHeightForWidth());
        playerchooseexit->setSizePolicy(sizePolicy2);
        QFont font4;
        font4.setPointSize(14);
        playerchooseexit->setFont(font4);

        verticalLayout_2->addWidget(playerchooseexit);


        gridLayout->addWidget(widget, 0, 1, 3, 1);

        line = new QFrame(playerchoose);
        line->setObjectName("line");
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 1, 0, 1, 1);

        funcwidget = new QWidget(playerchoose);
        funcwidget->setObjectName("funcwidget");
        gridLayout_2 = new QGridLayout(funcwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        IPLE = new QLineEdit(funcwidget);
        IPLE->setObjectName("IPLE");
        QFont font5;
        font5.setPointSize(12);
        IPLE->setFont(font5);

        gridLayout_2->addWidget(IPLE, 0, 2, 1, 2);

        label_2 = new QLabel(funcwidget);
        label_2->setObjectName("label_2");
        label_2->setFont(font5);

        gridLayout_2->addWidget(label_2, 1, 0, 1, 2);

        PORTLE = new QLineEdit(funcwidget);
        PORTLE->setObjectName("PORTLE");
        PORTLE->setFont(font5);

        gridLayout_2->addWidget(PORTLE, 1, 2, 1, 2);

        label = new QLabel(funcwidget);
        label->setObjectName("label");
        label->setFont(font5);

        gridLayout_2->addWidget(label, 0, 0, 1, 2);

        displaylbl = new QLabel(funcwidget);
        displaylbl->setObjectName("displaylbl");
        sizePolicy.setHeightForWidth(displaylbl->sizePolicy().hasHeightForWidth());
        displaylbl->setSizePolicy(sizePolicy);
        displaylbl->setFont(font5);

        gridLayout_2->addWidget(displaylbl, 2, 0, 1, 4);

        connectbtn = new QPushButton(funcwidget);
        connectbtn->setObjectName("connectbtn");
        connectbtn->setFont(font2);

        gridLayout_2->addWidget(connectbtn, 4, 0, 1, 4);

        startgame = new QPushButton(funcwidget);
        startgame->setObjectName("startgame");
        QFont font6;
        font6.setFamilies({QString::fromUtf8("\345\215\216\346\226\207\344\270\255\345\256\213")});
        font6.setPointSize(20);
        startgame->setFont(font6);

        gridLayout_2->addWidget(startgame, 5, 0, 1, 4);


        gridLayout->addWidget(funcwidget, 2, 0, 1, 1);


        retranslateUi(playerchoose);

        QMetaObject::connectSlotsByName(playerchoose);
    } // setupUi

    void retranslateUi(QWidget *playerchoose)
    {
        playerchoose->setWindowTitle(QCoreApplication::translate("playerchoose", "Form", nullptr));
        player1->setText(QCoreApplication::translate("playerchoose", "\347\216\251\345\256\2661", nullptr));
        hint->setText(QCoreApplication::translate("playerchoose", "\346\217\220\347\244\272\357\274\232\347\202\271\345\207\273\344\270\212\351\235\242\347\232\204\346\241\206\345\217\257\344\273\245\346\233\264\346\224\271\345\220\215\345\255\227", nullptr));
        player1inf->setText(QString());
        player1select->setText(QCoreApplication::translate("playerchoose", "\351\200\211\345\256\232", nullptr));
        label_3->setText(QCoreApplication::translate("playerchoose", "\346\211\200\346\234\211\345\215\241\347\273\204", nullptr));
        playerchooseexit->setText(QCoreApplication::translate("playerchoose", "\350\277\224\345\233\236\344\270\273\351\241\265\351\235\242", nullptr));
        label_2->setText(QCoreApplication::translate("playerchoose", "\347\253\257\345\217\243\345\217\267\357\274\232", nullptr));
        label->setText(QCoreApplication::translate("playerchoose", "IP\345\234\260\345\235\200\357\274\232", nullptr));
        displaylbl->setText(QCoreApplication::translate("playerchoose", "\346\202\250\350\277\230\346\262\241\346\234\211\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250\357\274\201", nullptr));
        connectbtn->setText(QCoreApplication::translate("playerchoose", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", nullptr));
        startgame->setText(QCoreApplication::translate("playerchoose", "\350\277\233\345\205\245\345\257\271\346\210\230!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class playerchoose: public Ui_playerchoose {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYERCHOOSE_H
