/********************************************************************************
** Form generated from reading UI file 'retlabel.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RETLABEL_H
#define UI_RETLABEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_retlabel
{
public:
    QGridLayout *gridLayout;
    QLabel *attack;
    QLabel *blood;
    QLabel *label;
    QLabel *selected;

    void setupUi(QWidget *retlabel)
    {
        if (retlabel->objectName().isEmpty())
            retlabel->setObjectName("retlabel");
        retlabel->resize(400, 300);
        gridLayout = new QGridLayout(retlabel);
        gridLayout->setObjectName("gridLayout");
        attack = new QLabel(retlabel);
        attack->setObjectName("attack");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(attack->sizePolicy().hasHeightForWidth());
        attack->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamilies({QString::fromUtf8("Times New Roman")});
        font.setPointSize(16);
        font.setBold(true);
        attack->setFont(font);

        gridLayout->addWidget(attack, 2, 0, 1, 1);

        blood = new QLabel(retlabel);
        blood->setObjectName("blood");
        sizePolicy.setHeightForWidth(blood->sizePolicy().hasHeightForWidth());
        blood->setSizePolicy(sizePolicy);
        blood->setFont(font);
        blood->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(blood, 2, 2, 1, 1);

        label = new QLabel(retlabel);
        label->setObjectName("label");
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        gridLayout->addWidget(label, 1, 0, 1, 3);

        selected = new QLabel(retlabel);
        selected->setObjectName("selected");
        sizePolicy.setHeightForWidth(selected->sizePolicy().hasHeightForWidth());
        selected->setSizePolicy(sizePolicy);
        selected->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(selected, 2, 1, 1, 1);


        retranslateUi(retlabel);

        QMetaObject::connectSlotsByName(retlabel);
    } // setupUi

    void retranslateUi(QWidget *retlabel)
    {
        retlabel->setWindowTitle(QCoreApplication::translate("retlabel", "Form", nullptr));
        attack->setText(QString());
        blood->setText(QString());
        label->setText(QString());
        selected->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class retlabel: public Ui_retlabel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RETLABEL_H
