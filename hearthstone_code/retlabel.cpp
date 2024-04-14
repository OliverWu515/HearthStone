#include "retlabel.h"
#include "ui_retlabel.h"
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>

retlabel::retlabel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::retlabel)
{
    ui->setupUi(this);
    ui->label->setFixedHeight(this->height()*0.45);
}

void retlabel::mousePressEvent(QMouseEvent *ev)
{
    //如果单击了就触发clicked信号
    if (ev->button() == Qt::LeftButton) emit labelclicked();
}

void retlabel::drawcardpic(int cardid)
{
    QPixmap pix;
    //QPixmap pix1;
    QString pixname;
    pixname = QString::fromStdString(":1/pic/")+QString::number(cardid)+QString::fromStdString(".png");
    bool ret = pix.load(pixname);
    //pix1=pix.copy(0,0,pix.width(),pix.height()*0.55);
    if(!ret)
    {
        QMessageBox::information(this,"提示","图片加载失败!");
        return;
    }
    ui->label->setPixmap(pix.scaled(ui->label->width()*1.1,ui->label->height()*1.1,Qt::KeepAspectRatio));
}
void retlabel::SetBldAtk(int bld,int atk)
{
    ui->blood->setText(QString::number(bld));
    ui->attack->setText(QString::number(atk));
}
void retlabel::SetSleep(bool sleeping)
{
    if(sleeping) ui->selected->setText("休眠中");
    else ui->selected->clear();
}
void retlabel::enterEvent(QEnterEvent *event)
{
    emit showprompt();
}

void retlabel::leaveEvent(QEvent *event)
{
    emit hideprompt();
}

void retlabel::selected(bool isselected)
{
    if(!isselected) ui->selected->setText("√");
    else ui->selected->setText("");
}

retlabel::~retlabel()
{
    delete ui;
}
