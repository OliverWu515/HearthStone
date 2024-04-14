#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QPushButton>
#include<QTimer>
#include<QLabel>
#include<QMessageBox>
#include <card.h>
#include <deck.h>
#include <QAction>
#include <uistyle.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showFullScreen();
    setWindowIcon(QIcon(":/1/pic/logo_1.jpg"));
    setWindowTitle("简易炉石传说游戏");
    //QImage *img1 = new QImage;
    QPixmap *img1 = new QPixmap();
    if(!(img1->load(":/1/pic/1011.jpg")))
    {
        QMessageBox::information(this,"图像打开失败","图像打开失败！");
        delete img1;
        return;
    }
    //构建后才有控件！
    QLabel *bglbl=new QLabel;
    bglbl->setPixmap(*img1);
    bglbl->setScaledContents(true);
    bglbl->setParent(this);
    bglbl->show();
    bglbl->setGeometry(0,0,this->width(),this->height());
    img1->scaled(bglbl->width(),bglbl->height(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    //设置按钮，为之后做准备
    ui->exitbtn->setEnabled(false);
    ui->startbtn->setEnabled(false);
    ui->selectbtn->setEnabled(false);

    connect(ui->exitbtn,&QPushButton::clicked,[=](){
        QMessageBox::information(this,"感谢使用","开发：210320621吴俊达, \n210320623万珩；\n指导老师：吴晓军");
        this->close();
    });

    connect(ui->selectbtn,&QPushButton::clicked,this,&MainWindow::deckscenesetup);
    connect(ui->startbtn,&QPushButton::clicked,this,&MainWindow::playerchoosesetup);
    //启动图片显示5s 测试时注释，节省时间
    //QTimer::singleShot(5000, [=](){
    delete bglbl;
    ui->widget1->show();
    ui->startbtn->setEnabled(true);
    ui->selectbtn->setEnabled(true);
    ui->exitbtn->setEnabled(true);
    setWindowTitle("简易炉石传说游戏：请选择功能");
    // });
}

void MainWindow::deckscenesetup()
{
    choosedeck=new deck_and_heros;
    choosedeck->show();
    this->hide();
    connect(choosedeck,&deck_and_heros::chooseSceneBack,this,&MainWindow::deckscenedelete);
}
void MainWindow::deckscenedelete()
{
    delete choosedeck;
    choosedeck=nullptr;
    this->show();
}
void MainWindow::playerchoosesetup()
{
    this->abletostartgame();
    if(validdecknum==0)
        QMessageBox::information(this,"温馨提示","只有含有30张卡牌的卡组才可供对战使用。目前还没有符合条件的卡组，请先新建或编辑卡组！");
    else
    {
        playerchoosedeck=new playerchoose;
        playerchoosedeck->show();
        this->hide();
        connect(playerchoosedeck,&playerchoose::chooseSceneBack,this,&MainWindow::playerchoosedelete);
    }
}
void MainWindow::playerchoosedelete()
{
    //    this->setGeometry(playerchoosedeck->geometry());留作备用
    delete playerchoosedeck;
    playerchoosedeck=nullptr;
    this->show();
}
void MainWindow::abletostartgame()
{
    validdecknum=0;
    int totaldecknum=0;
    totaldecknum=GetDeckNum();
    totaldecknum++;
    deck deck1[totaldecknum];
    for(int i=1;i<totaldecknum;i++) deck1[i]=ReadDeck(i);
    for(int i=1;i<totaldecknum;i++)
    {
        if(deck1[i].Sum!=30)  continue;
        validdecknum++;
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
