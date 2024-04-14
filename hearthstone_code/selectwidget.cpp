#include "selectwidget.h"
#include "ui_selectwidget.h"
#include <QDebug>
#include <QString>
#include <QMessageBox>

selectwidget::selectwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::selectwidget)
{
    ui->setupUi(this);
    buttonlist[0]=ui->card1;
    buttonlist[1]=ui->card2;
    buttonlist[2]=ui->card3;
    buttonlist[3]=ui->card4;
    buttonlist[4]=ui->card5;
    buttonlist[5]=ui->card6;
}
//给每个按钮画上卡牌图片
void selectwidget::setcards(int cardnum,int cardindex[],int startnum)
{
    for(int i=0;i<cardnum;i++)
    {
        int index1,index2;
        index1=i+startnum;
        index2=cardindex[index1];
        QPixmap pix;
        QString pixname;
        pixname = QString::fromStdString(":1/pic/")+QString::number(index2)+QString::fromStdString(".png");
        bool ret = pix.load(pixname);
        if(!ret)
        {
            QMessageBox::information(this,"提示","图片加载失败!");
            return;
        }
        buttonlist[i]->setStyleSheet("QToolButton{border:0px;}");
        buttonlist[i]->setIcon(pix);
        buttonlist[i]->setIconSize(QSize(pix.width(),pix.height()));
    }
    for(int i=cardnum;i<6;i++)
    {
        QPixmap pix;
        bool ret = pix.load(":/1/pic/VAN_CS1_129.png");
        if(!ret)
        {
            QMessageBox::information(this,"提示","图片加载失败!");
            return;
        }
        buttonlist[i]->setStyleSheet("QToolButton{border:0px;}");
        buttonlist[i]->setIcon(pix);
        buttonlist[i]->setIconSize(QSize(pix.width(),pix.height()));
    }
}
//按钮数目不足页面特殊处理
void selectwidget::lessbutton(int btnnum)
{
    QSizePolicy size_hint;
    size_hint = buttonlist[0]->sizePolicy();//想要隐藏的部件为buttonlist[i]
    size_hint.setRetainSizeWhenHidden(true);
    for(int i=btnnum;i<=5;i++)
    {
        buttonlist[i]->setSizePolicy(size_hint);
        buttonlist[i]->hide();
        buttonlist[i]->setDisabled(true);
    }
}
//处理每个卡组的意义
void selectwidget::setdecks(int cardnum, int startnum)
{
    for(int i=0;i<cardnum;i++)
    {
        int index;
        index=i+startnum;
        QPixmap pix;
        QString pixname=NULL;
        pixname = QString::fromStdString(":1/pic/HERO_0")+QString::number(index)+QString::fromStdString(".png");
        bool ret = pix.load(pixname);
        if(!ret)
        {
            QMessageBox::information(this,"提示","图片加载失败!");
            return;
        }
        buttonlist[i]->setStyleSheet("QToolButton{border:0px;}");
        buttonlist[i]->setIcon(pix);
        buttonlist[i]->setIconSize(QSize(pix.width(),pix.height()));
        buttonlist[i]->setDisabled(true);
    }
    for(int i=cardnum;i<6;i++)
    {
        QPixmap pix;
        bool ret = pix.load(":/1/pic/VAN_CS1_129.png");
        if(!ret)
        {
            QMessageBox::information(this,"提示","图片加载失败!");
            return;
        }
        buttonlist[i]->setStyleSheet("QToolButton{border:0px;}");
        buttonlist[i]->setIcon(pix);
        buttonlist[i]->setIconSize(QSize(pix.width(),pix.height()));
        buttonlist[i]->setDisabled(true);
    }
}
//释放掉之前设置过的icon,释放内存
void selectwidget::deleteicons()
{
    for(int i=0;i<6;i++) buttonlist[i]->setIcon(QIcon());
}
selectwidget::~selectwidget()
{
    delete ui;
}
