#include "firstchoose.h"
#include "ui_firstchoose.h"
#include <QGuiApplication>
#include <QScreen>
#include <QRect>
#include <QTimer>

firstchoose::firstchoose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::firstchoose)
{
    ui->setupUi(this);
    //获取窗口分辨率
    QRect mRect;
    mRect = QGuiApplication::primaryScreen()->geometry();
    //长宽设为窗口长宽的50%
    setFixedSize(mRect.width()*0.5,mRect.height()*0.5);
    ui->widget->setFixedSize(this->width()*0.95,this->height()*0.85);
    this->setWindowTitle("选择初始卡牌");
    this->setWindowFlags( Qt::WindowStaysOnTopHint
                         |Qt::CustomizeWindowHint
                          |Qt::WindowTitleHint
                          | Qt::WindowDoesNotAcceptFocus
                          | Qt::Tool
                          | Qt::X11BypassWindowManagerHint);
    ui->pushButton->setText("确定");
}

void firstchoose::fcsetup(int num,deck decktemp)
{
    srand(time(NULL));
    mylabel *fc[4]={nullptr};
    for(int i=0;i<num;i++)
    {
        fc[i] = new mylabel(ui->widget);
        fc[i]->setFixedSize(ui->widget->width()*(1.0/num-0.02),ui->widget->height());
        fc[i]->move(ui->widget->x()+ui->widget->width()/num*i,ui->widget->y());
        int randnum = rand()%30+1;
        for(int k=0;k<num;k++)
        {
            if(decktemp.CardID[randnum]==selected[k]||decktemp.CardID[randnum]==selected2[k])
            {
                randnum = rand()%30+1;
                k=-1;
            }
        }
        fc[i]->drawcardpic(decktemp.CardID[randnum]);
        selected[i]=decktemp.CardID[randnum];
        selected2[i]=decktemp.CardID[randnum];
        connect(fc[i],&mylabel::labelclicked,[=](){
            fc[i]->drawgraypic(selected[i]);
          changed[i]=true;
        });
    }
        connect(ui->pushButton,&QPushButton::clicked,[=](){
           if(buttonstatus){//如果已经选完将要退出
               emit chooseSceneBack(selected[0],selected[1],selected[2],selected[3]);
           }
               else{//如果只是选了一轮
               ui->pushButton->setEnabled(false);
               ui->pushButton->setText("请稍等");
               for(int i=0;i<num;i++)
               {
                   disconnect(fc[i],&mylabel::labelclicked,0,0);
                   if(changed[i])
                   {
                       int randnum = rand()%30+1;
                       for(int k=0;k<num;k++)
                       {
                           if(decktemp.CardID[randnum]==selected[k]||decktemp.CardID[randnum]==selected2[k])
                           {
                               randnum = rand()%30+1;
                               k=-1;
                           }
                       }
                       fc[i]->drawcardpic(decktemp.CardID[randnum]);
                       selected[i]=decktemp.CardID[randnum];
                   }
               }
               QTimer::singleShot(1000, [=](){
                  ui->pushButton->setEnabled(true);
                  buttonstatus=true;
                  ui->pushButton->setText("返回");
               });
           }
        });
}
firstchoose::~firstchoose()
{
    delete ui;
}
