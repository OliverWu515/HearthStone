/********************************************************************************
** Form generated from reading UI file 'deck_and_heros.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DECK_AND_HEROS_H
#define UI_DECK_AND_HEROS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_deck_and_heros
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QPushButton *editdeck;
    QPushButton *renamedeck;
    QPushButton *deletebtn;
    QPushButton *newdeck;
    QPushButton *returntolast;
    QListWidget *deckinf;
    QLabel *hintinformation;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QPushButton *lastpage;
    QLabel *pagenum;
    QStackedWidget *stackedWidget;
    QPushButton *nextpage;
    QLabel *prompt;

    void setupUi(QWidget *deck_and_heros)
    {
        if (deck_and_heros->objectName().isEmpty())
            deck_and_heros->setObjectName("deck_and_heros");
        deck_and_heros->resize(791, 370);
        gridLayout_2 = new QGridLayout(deck_and_heros);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        editdeck = new QPushButton(deck_and_heros);
        editdeck->setObjectName("editdeck");
        QFont font;
        font.setPointSize(12);
        editdeck->setFont(font);

        gridLayout->addWidget(editdeck, 1, 0, 1, 1);

        renamedeck = new QPushButton(deck_and_heros);
        renamedeck->setObjectName("renamedeck");
        renamedeck->setFont(font);

        gridLayout->addWidget(renamedeck, 0, 1, 1, 1);

        deletebtn = new QPushButton(deck_and_heros);
        deletebtn->setObjectName("deletebtn");
        deletebtn->setFont(font);

        gridLayout->addWidget(deletebtn, 1, 1, 1, 1);

        newdeck = new QPushButton(deck_and_heros);
        newdeck->setObjectName("newdeck");
        newdeck->setFont(font);

        gridLayout->addWidget(newdeck, 0, 0, 1, 1);

        returntolast = new QPushButton(deck_and_heros);
        returntolast->setObjectName("returntolast");
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(returntolast->sizePolicy().hasHeightForWidth());
        returntolast->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(14);
        returntolast->setFont(font1);

        gridLayout->addWidget(returntolast, 0, 2, 2, 1);


        gridLayout_2->addLayout(gridLayout, 3, 1, 1, 1);

        deckinf = new QListWidget(deck_and_heros);
        deckinf->setObjectName("deckinf");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(20);
        sizePolicy1.setHeightForWidth(deckinf->sizePolicy().hasHeightForWidth());
        deckinf->setSizePolicy(sizePolicy1);
        deckinf->setFrameShape(QFrame::Panel);

        gridLayout_2->addWidget(deckinf, 1, 1, 2, 1);

        hintinformation = new QLabel(deck_and_heros);
        hintinformation->setObjectName("hintinformation");
        QFont font2;
        font2.setFamilies({QString::fromUtf8("\346\245\267\344\275\223")});
        font2.setPointSize(14);
        hintinformation->setFont(font2);
        hintinformation->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(hintinformation, 0, 1, 1, 1);

        widget = new QWidget(deck_and_heros);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(10);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy2);
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setObjectName("gridLayout_3");
        lastpage = new QPushButton(widget);
        lastpage->setObjectName("lastpage");
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lastpage->sizePolicy().hasHeightForWidth());
        lastpage->setSizePolicy(sizePolicy3);
        QFont font3;
        font3.setPointSize(16);
        lastpage->setFont(font3);

        gridLayout_3->addWidget(lastpage, 1, 0, 1, 1);

        pagenum = new QLabel(widget);
        pagenum->setObjectName("pagenum");
        QFont font4;
        font4.setFamilies({QString::fromUtf8("Times New Roman")});
        font4.setPointSize(10);
        pagenum->setFont(font4);

        gridLayout_3->addWidget(pagenum, 2, 2, 1, 1);

        stackedWidget = new QStackedWidget(widget);
        stackedWidget->setObjectName("stackedWidget");

        gridLayout_3->addWidget(stackedWidget, 1, 1, 2, 1);

        nextpage = new QPushButton(widget);
        nextpage->setObjectName("nextpage");
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(nextpage->sizePolicy().hasHeightForWidth());
        nextpage->setSizePolicy(sizePolicy4);
        nextpage->setFont(font3);

        gridLayout_3->addWidget(nextpage, 1, 2, 1, 1);

        prompt = new QLabel(widget);
        prompt->setObjectName("prompt");
        prompt->setFont(font2);
        prompt->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(prompt, 0, 0, 1, 3);


        gridLayout_2->addWidget(widget, 0, 0, 4, 1);


        retranslateUi(deck_and_heros);

        QMetaObject::connectSlotsByName(deck_and_heros);
    } // setupUi

    void retranslateUi(QWidget *deck_and_heros)
    {
        deck_and_heros->setWindowTitle(QCoreApplication::translate("deck_and_heros", "Form", nullptr));
        editdeck->setText(QCoreApplication::translate("deck_and_heros", "PushButton", nullptr));
        renamedeck->setText(QCoreApplication::translate("deck_and_heros", "PushButton", nullptr));
        deletebtn->setText(QCoreApplication::translate("deck_and_heros", "PushButton", nullptr));
        newdeck->setText(QCoreApplication::translate("deck_and_heros", "PushButton", nullptr));
        returntolast->setText(QCoreApplication::translate("deck_and_heros", "PushButton", nullptr));
        hintinformation->setText(QCoreApplication::translate("deck_and_heros", "\346\211\200\346\234\211\345\215\241\347\273\204", nullptr));
        lastpage->setText(QString());
        pagenum->setText(QString());
        nextpage->setText(QString());
        prompt->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class deck_and_heros: public Ui_deck_and_heros {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DECK_AND_HEROS_H
