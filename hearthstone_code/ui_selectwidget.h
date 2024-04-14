/********************************************************************************
** Form generated from reading UI file 'selectwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTWIDGET_H
#define UI_SELECTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_selectwidget
{
public:
    QGridLayout *gridLayout;
    QToolButton *card1;
    QToolButton *card3;
    QToolButton *card4;
    QToolButton *card5;
    QToolButton *card6;
    QToolButton *card2;

    void setupUi(QWidget *selectwidget)
    {
        if (selectwidget->objectName().isEmpty())
            selectwidget->setObjectName("selectwidget");
        selectwidget->resize(400, 300);
        gridLayout = new QGridLayout(selectwidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        card1 = new QToolButton(selectwidget);
        card1->setObjectName("card1");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(card1->sizePolicy().hasHeightForWidth());
        card1->setSizePolicy(sizePolicy);

        gridLayout->addWidget(card1, 0, 0, 1, 1);

        card3 = new QToolButton(selectwidget);
        card3->setObjectName("card3");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(card3->sizePolicy().hasHeightForWidth());
        card3->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(card3, 0, 2, 1, 1);

        card4 = new QToolButton(selectwidget);
        card4->setObjectName("card4");
        sizePolicy1.setHeightForWidth(card4->sizePolicy().hasHeightForWidth());
        card4->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(card4, 2, 0, 1, 1);

        card5 = new QToolButton(selectwidget);
        card5->setObjectName("card5");
        sizePolicy1.setHeightForWidth(card5->sizePolicy().hasHeightForWidth());
        card5->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(card5, 2, 1, 1, 1);

        card6 = new QToolButton(selectwidget);
        card6->setObjectName("card6");
        sizePolicy1.setHeightForWidth(card6->sizePolicy().hasHeightForWidth());
        card6->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(card6, 2, 2, 1, 1);

        card2 = new QToolButton(selectwidget);
        card2->setObjectName("card2");
        sizePolicy1.setHeightForWidth(card2->sizePolicy().hasHeightForWidth());
        card2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(card2, 0, 1, 1, 1);


        retranslateUi(selectwidget);

        QMetaObject::connectSlotsByName(selectwidget);
    } // setupUi

    void retranslateUi(QWidget *selectwidget)
    {
        selectwidget->setWindowTitle(QCoreApplication::translate("selectwidget", "Form", nullptr));
        card1->setText(QString());
        card3->setText(QString());
        card4->setText(QString());
        card5->setText(QString());
        card6->setText(QString());
        card2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class selectwidget: public Ui_selectwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTWIDGET_H
