#include "mylabel.h"
#include <QPixmap>
#include <QDebug>
#include <QMessageBox>

mylabel::mylabel(QWidget *parent) : QLabel(parent)
{
    //this->setMouseTracking(true);
}

void mylabel::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) emit labelclicked();
    if(ev->button() == Qt::LeftButton&&ev->type()==QEvent::MouseButtonDblClick) emit labeldblclicked();
//    return QLabel::mousePressEvent(ev);
}

void mylabel::drawheropic(int heroid)
{
    QPixmap pix;
    QString pixname=NULL;
    pixname = QString::fromStdString(":1/pic/HERO_0")+QString::number(heroid)+QString::fromStdString(".png");
    bool ret = pix.load(pixname);
    if(!ret)
    {
        QMessageBox::information(this,"提示","图片加载失败!");
        return;
    }
    this->setPixmap(pix.scaled(this->width()*1.2,this->height()*1.2,Qt::KeepAspectRatio));
}
void mylabel::drawskillpic(bool d, int heroid)
{
    QPixmap pix;
    QString pixname=NULL;
    if(d)  pixname = QString::fromStdString(":1/pic/SKILL_0")+QString::number(heroid)+QString::fromStdString(".png");
    else pixname=":/1/pic/VAN_CS1_129.png";//将来换成白卡文件名
    bool ret=pix.load(pixname);
    if(!ret)
    {
        QMessageBox::information(this,"提示","图片加载失败!");
        return;
    }
    this->setPixmap(pix.scaled(this->width()*1.2,this->height()*1.2,Qt::KeepAspectRatio));
}
void mylabel::drawcardpic(int cardid)
{
    QPixmap pix;
    QString pixname;
    pixname = QString::fromStdString(":1/pic/")+QString::number(cardid)+QString::fromStdString(".png");
    bool ret = pix.load(pixname);
    if(!ret)
    {
        QMessageBox::information(this,"提示","图片加载失败!");
        return;
    }
    this->setPixmap(pix.scaled(this->width(),this->height(),Qt::KeepAspectRatio));
}

void mylabel::drawgraypic(int cardid)
{
    QString pixname;
    pixname = QString::fromStdString(":1/pic/")+QString::number(cardid)+QString::fromStdString(".png");
    QImage *image=new QImage(pixname);
    QImage *gray_image = new QImage;
    *gray_image = image->convertToFormat(QImage::Format_Grayscale8,Qt::AutoColor);
    QPixmap *pixmap=new QPixmap();
    pixmap->convertFromImage(*gray_image);
    this->setPixmap(pixmap->scaled(this->width(),this->height(),Qt::KeepAspectRatio));
    delete gray_image;
    gray_image=nullptr;
    delete pixmap;
    pixmap=nullptr;
    delete image;
    image=nullptr;
}

void mylabel::enterEvent(QEnterEvent *event)
{
    emit showprompt();
    qDebug()<<1;
}

void mylabel::leaveEvent(QEvent *event)
{
    emit hideprompt();
    qDebug()<<2;
}
