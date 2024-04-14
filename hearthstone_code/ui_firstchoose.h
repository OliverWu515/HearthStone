/********************************************************************************
** Form generated from reading UI file 'firstchoose.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIRSTCHOOSE_H
#define UI_FIRSTCHOOSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_firstchoose
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QWidget *widget;
    QPushButton *pushButton;

    void setupUi(QWidget *firstchoose)
    {
        if (firstchoose->objectName().isEmpty())
            firstchoose->setObjectName("firstchoose");
        firstchoose->resize(411, 308);
        verticalLayout = new QVBoxLayout(firstchoose);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(firstchoose);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\215\216\346\226\207\346\245\267\344\275\223")});
        font.setPointSize(14);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        widget = new QWidget(firstchoose);
        widget->setObjectName("widget");
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(widget);

        pushButton = new QPushButton(firstchoose);
        pushButton->setObjectName("pushButton");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\215\216\346\226\207\344\270\255\345\256\213")});
        font1.setPointSize(14);
        pushButton->setFont(font1);

        verticalLayout->addWidget(pushButton);


        retranslateUi(firstchoose);

        QMetaObject::connectSlotsByName(firstchoose);
    } // setupUi

    void retranslateUi(QWidget *firstchoose)
    {
        firstchoose->setWindowTitle(QCoreApplication::translate("firstchoose", "Form", nullptr));
        label->setText(QCoreApplication::translate("firstchoose", "\350\277\233\350\241\214\351\200\211\346\213\251", nullptr));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class firstchoose: public Ui_firstchoose {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIRSTCHOOSE_H
