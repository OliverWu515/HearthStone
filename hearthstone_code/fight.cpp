#include "fight.h"
#include "ui_fight.h"
#include <QDebug>
#include <mylabel.h>
#include <QMessageBox>
#include <algorithm>
#include <QHBoxLayout>
#include <string.h>
#include <QMetaType>
#include <QScreen>
#include <QRect>

fight::fight(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fight)
{
    ui->setupUi(this);
    setWindowTitle("对战界面");
    //showFullScreen();
    //获取窗口分辨率
    QRect mRect;
    mRect = QGuiApplication::primaryScreen()->geometry();
    //最大长宽设为窗口长宽的80%
    setFixedSize(mRect.width()*0.8,mRect.height()*0.8);
    setWindowIcon(QIcon(":/1/pic/logo_1.jpg"));

    // 设置随从、手牌、英雄图框长宽
    ui->myherolbl->setFixedHeight(this->height()*0.22);
    ui->myboard->setFixedHeight(this->height()*0.22);
    ui->rivalboard->setFixedHeight(this->height()*0.22);
    ui->rivalherolbl->setFixedHeight(this->height()*0.22);
    ui->mycard->setFixedSize(this->width()*0.7,this->height()*0.22);

    // 按钮及时间轴初始化
    ui->endrnd->setEnabled(false);
    ui->lose->setEnabled(false);
    ui->timebar->hide();
    ui->widget->setFixedSize(this->width()*0.3,this->height()*0.2);
    ui->timebar->setStyleSheet("QProgressBar::chunk{border-radius:5px;background:rgba(0,0,0,150)}");
    ui->timebar->setAlignment(Qt::AlignHCenter);

    ui->prompttext->setFont(QFont("楷体",11));

    // 设置调色盘
    QPalette pa,pa1,pa2;
    pa.setBrush(QPalette::Window, Qt::transparent);
    ui->timebar->setPalette(pa);
    pa1.setBrush(QPalette::Base, QColor(0x00,0x00,0x00,0x15));
    ui->information->setPalette(pa1);
    pa2.setBrush(QPalette::WindowText, Qt::black);
    ui->information->setPalette(pa2);
    ui->prompttext->setPalette(pa2);

    // 卡组初始化，将所有卡牌生命值置为最大
    SetCard(Allcard);
    for(int i=1;i<=MaxCard;i++)
    {
        Allcard[i].Minion.Health=Allcard[i].Minion.MaxHealth;
        Allcard[i].Minion.Attack=Allcard[i].Minion.MaxAttack;
    }
    qRegisterMetaType<MINION>("MINION");
    qRegisterMetaType<SPELL>("SPELL");
    qRegisterMetaType<WEAPON>("WEAPON");
    qRegisterMetaType<CARD>("CARD");
}

void fight::fightsetup(QString myname,QTcpSocket *_socket,int myid,int rivalid,deck newdeck)
{
    ui->myname->setText(myname);  // 设置本玩家名
    ui->myherolbl->drawheropic(newdeck.Hero);  // 显示己方英雄
    // 获取玩家与对手的编号
    this->myid=myid;
    this->rivalid=rivalid;
    this->mydeck=newdeck;

    // TCP/IP通信部分
    this->_socket=_socket;  // 准备套接字
    connect(_socket,&QTcpSocket::readyRead, this,&fight::slotGetServerData);  // 将套接字接收信息关联至处理信息函数
    QByteArray buf;
    QDataStream out(&buf,QIODevice::WriteOnly);
    out<<SETUP<<myname<<true<<rivalid<<newdeck.Hero;  // 将己方玩家名、对方编号和己方英雄名传给服务器
    _socket->write(buf);
}

void fight::slotGetServerData()
{
    QDataStream in;
    in.setDevice(_socket);
    while(_socket && _socket->bytesAvailable())
    {
        int type;
        in>>type;

        switch(type)
        {
        case SETUP:
        {
            // 获取对方玩家名
            QString rivalname;
            in>>rivalname;
            ui->rivalnamelbl->setText(rivalname);
            // 获取先后手信息
            in>>first;
            turn=first;
            // 获取对方英雄id、显示对方英雄并刷新血量
            int rivalheroid;
            in>>rivalheroid;
            ui->rivalherolbl->drawheropic(rivalheroid);
            refreshherobld();

            // 初次选卡页面，先手3张，后手4张
            fcscene=new firstchoose(this);
            if(first)
            {
                displayinfos("您取得了先手");
                ui->endrnd->setText("结束回合");
                fcscene->fcsetup(3,this->mydeck);
            }
            else
            {
                displayinfos("您取得了后手");
                ui->endrnd->setText("对手回合");
                fcscene->fcsetup(4,this->mydeck);
            }
            fcscene->show();
            connect(fcscene,&firstchoose::chooseSceneBack,[=](int c1,int c2,int c3,int c4){
                bool c1flag=true,c2flag=true,c3flag=true,c4flag=false;
                if(c4) c4flag=true;
                int randnum[31];
                for(int j=1;j<=30;j++) randnum[j]=j;
                std::random_shuffle(randnum+1,randnum+30); // 使卡组压入牌库时是乱序的
                for(int j=1;j<=30;j++)
                {
                    if(c1flag&&mydeck.CardID[randnum[j]]==c1)
                    {
                        handcard.append(Allcard[c1]);
                        c1flag=false;
                        continue;
                    }
                    if(c2flag&&mydeck.CardID[randnum[j]]==c2)
                    {
                        handcard.append(Allcard[c2]);
                        c2flag=false;
                        continue;
                    }
                    if(c3flag&&mydeck.CardID[randnum[j]]==c3)
                    {
                        handcard.append(Allcard[c3]);
                        c3flag=false;
                        continue;
                    }
                    if(c4flag&&mydeck.CardID[randnum[j]]==c4)
                    {
                        handcard.append(Allcard[c4]);
                        c4flag=false;
                        continue;
                    }
                    depositcard.push(Allcard[mydeck.CardID[randnum[j]]]);
                }
                ini1=true;  // 己方允许初始化
                handsetup();  // 将首轮抽到的牌置入手牌
                delete fcscene;
                fcscene=nullptr;
                // 暂时不允许操作，因为对方是否准备好未确定
                for(int i=0;i<handcard.size();i++)
                {
                    disconnect(handlbl[i],&mylabel::labelclicked,0,0);
                    disconnect(handlbl[i],&mylabel::labeldblclicked,0,0);
                }
                for(int i=0;i<retinuecard.size();i++)
                {
                    disconnect(retinuelbl[i],&retlabel::labelclicked,0,0);
                }
                for(int i=0;i<rivalretcard.size();i++)
                {
                    disconnect(rivalretlbl[i],&retlabel::labelclicked,0,0);
                }
                disconnect(ui->rivalherolbl,&mylabel::labelclicked,0,0);
                initialize();
                ui->lose->setEnabled(true);  // 使能认输按钮
            });
        }
            break;
        case REFRESH1:
        {
            int rivalcardnum;
            in>>rivalcardnum;
            ui->rivalcard->setText("对手现持有"+QString::number(rivalcardnum)+"张牌");
            in>>ini2;
            initialize();
        }
            break;
        case REFRESH2:
        {
            int size;
            in>>size;
            rivalretcard.clear();
            QVector<CARD>().swap(rivalretcard);
            for(int i=0;i<size;i++)
            {
                CARD TEMP;
                QString a,b;
                in>>TEMP.ID>>TEMP.Cost>>TEMP.Hero
                        //>>a>>TEMP.Rarity>>b>>TEMP.Type;
                        >>a>>TEMP.Rarity>>TEMP.Type;
                strcpy(TEMP.Name,a.toUtf8().data());
                //strcpy(TEMP.Description,b.toUtf8().data());
                if(TEMP.Type==1)
                {
                    in>>TEMP.Minion.Taunt>>TEMP.Minion.Charge
                            >>TEMP.Minion.Frozen>>TEMP.Minion.Stealth
                            >>TEMP.Minion.Windfury>>TEMP.Minion.DivineShield
                            >>TEMP.Minion.Attack>>TEMP.Minion.MaxAttack
                            >>TEMP.Minion.Health>>TEMP.Minion.MaxHealth;
                }
                else if(TEMP.Type==2)
                {
                    in>>TEMP.Weapon.Attack>>TEMP.Weapon.Durability;
                }
                rivalretcard.append(TEMP);
            }
            rivalretsetup();
        }
            break;
        case REFRESH3:
        {
            in>>rivalheroblood>>myheroblood;
            ui->myherobld->setText("当前血量"+QString::number(myheroblood));
            ui->rivalherobld->setText("当前血量"+QString::number(rivalheroblood));
            //不能再次调用refreshherobld函数,否则一直收发导致死循环
        }
            break;
        case REFRESH4:
        {
            in>>currentrivalcrys;
            in>>rivalcrys;
            //不能再次调用refreshcrys函数,否则一直收发导致死循环
            ui->rivalcrystal->setText("法力水晶"+QString::number(currentrivalcrys)+"/"+QString::number(rivalcrys));
        }
            break;
        case REFRESH5:
        {
            int size;
            in>>size;
            retinuecard.clear();
            QVector<CARD>().swap(retinuecard);
            for(int i=0;i<size;i++)
            {
                CARD TEMP;
                QString a;
//                QString b;
                in>>TEMP.ID>>TEMP.Cost>>TEMP.Hero
                        //>>a>>TEMP.Rarity>>b>>TEMP.Type;
                        >>a>>TEMP.Rarity>>TEMP.Type;
                strcpy(TEMP.Name,a.toUtf8().data());
                //strcpy(TEMP.Description,b.toUtf8().data());
                if(TEMP.Type==1)
                {
                    in>>TEMP.Minion.Taunt>>TEMP.Minion.Charge
                            >>TEMP.Minion.Frozen>>TEMP.Minion.Stealth
                            >>TEMP.Minion.Windfury>>TEMP.Minion.DivineShield
                            >>TEMP.Minion.Attack>>TEMP.Minion.MaxAttack
                            >>TEMP.Minion.Health>>TEMP.Minion.MaxHealth;
                }
                else if(TEMP.Type==2)
                {
                    in>>TEMP.Weapon.Attack>>TEMP.Weapon.Durability;
                }
                retinuecard.append(TEMP);
            }
            retinuesetup();
        }
            break;
        case REFRESHINFO:
        {
            int cnt;  // 消息条数
            in>>cnt;
            QVector<QString> st;
            in>>st;
            for(int i=0;i<cnt;i++) displayinfos(st.at(i));
        }
            break;
        case ENDROUND:
        {
            turn=true;
            ui->endrnd->setEnabled(true);
            ui->endrnd->setText("结束回合");
            connect(ui->rivalherolbl,&mylabel::labelclicked,[=](){
                heroattack();
            });
            _timer.start(1000);
            _timecount=100;
            connect(&_timer,&QTimer::timeout,this,&fight::timerslot);
            ui->timebar->show();
            round++;
            if(round<10) crystal=round;
            else crystal=10;
            currentcrys=crystal;
            refreshcrys();
            drawcard(1);// 抽1张卡牌
            attacktime.clear(); // 重置攻击次数
            QVector<uint8_t>().swap(attacktime); // 置空，方便后续append与索引读取操作
            for(int i=0;i<retinuecard.size();i++)
            {
                if(retinuecard.at(i).Minion.Windfury) attacktime.append(2);
                else attacktime.append(1);
                retinuecard[i].Minion.Charge=true;
            }
            handsetup();
            retinuesetup();
            rivalretsetup();
        }
            break;
        case QUITGAME:
        {
            delete fcscene;
            fcscene=nullptr;
            bool run_or_drop;
            in>>run_or_drop;
            _timer.stop();
            if(run_or_drop)
                QMessageBox::information(this,"提示","对手逃跑了，您取得了对战的胜利！");
            else
                QMessageBox::information(this,"提示","对手认输了，您取得了对战的胜利！");
            emit chooseSceneBack();
        }
            break;
        case WIN:
        {
            delete fcscene;
            fcscene=nullptr;
            QMessageBox::information(this,"提示","很遗憾，您被对手打败了。");
            emit chooseSceneBack();
        }
            break;
        }
    }
}

// 专门处理最开始时可能出现的双方玩家选卡异步情形
void fight::initialize()
{
    if (ini1&&ini2)
    {
        if(turn)
        {
            ui->timebar->show();
            ui->endrnd->setEnabled(true);
            _timer.start(1000);
            connect(&_timer,&QTimer::timeout,this,&fight::timerslot);
            connect(ui->rivalherolbl,&mylabel::labelclicked,[=](){
                heroattack();
            });
            handsetup();
        }
        if(first) round=1;
        else round=0;
        crystal=round;
        currentcrys=crystal;
        refreshcrys();
        // 只允许初始化一次
        ini1=false;
        ini2=false;
    }
}

void fight::handsetup()
{
    currentselect_hand=-1;
    for(int j=0;j<10;j++)
    {
        // 释放所有内存，并且复位选中标记
        if(handlbl[j]!=nullptr)
        {
            delete handlbl[j];
            handlbl[j]=nullptr;
        }
        selected_hand[j]=false;
    }
    delete ui->mycard->layout();
    QHBoxLayout *m_lay=new QHBoxLayout;
    m_lay->setAlignment(Qt::AlignLeft);
    ui->mycard->setLayout(m_lay);
    for(int i=0;i<handcard.size();i++)
    {
        handlbl[i] = new mylabel;
        handlbl[i]->setFixedSize(ui->mycard->width()*0.095,ui->mycard->height()*0.75);
        m_lay->addWidget(handlbl[i]);
        handlbl[i]->drawcardpic(handcard.at(i).ID);
        connect(handlbl[i],&mylabel::labelclicked,[this,i](){
            if(selected_hand[i]) // 已选中，则取消选中
            {
                currentselect_hand=-1;
                handlbl[i]->setFrameShape(QFrame::NoFrame);
                handlbl[i]->setStyleSheet("");
            }
            else
            {
                // 解除原来被选中的手牌的选中状态
                if(currentselect_hand!=-1)
                {
                    selected_hand[currentselect_hand]=!selected_hand[currentselect_hand];
                    handlbl[currentselect_hand]->setFrameShape(QFrame::NoFrame);
                    handlbl[currentselect_hand]->setStyleSheet("");
                }
                // 解除随从牌的选中状态
                if(currentselect_retinue!=-1)
                {
                    retinuelbl[currentselect_retinue]->selected(selected_retinue[currentselect_retinue]);
                    selected_retinue[currentselect_retinue]=!selected_retinue[currentselect_retinue];
                    currentselect_retinue=-1;
                }
                // 设置现在手牌选定状态
                currentselect_hand=i;
                handlbl[i]->setFrameShape(QFrame::Box);
                handlbl[i]->setStyleSheet("border-width: 1px;border-style: solid;border-color: rgb(255, 170, 0);");
            }
            selected_hand[i]=!selected_hand[i];
        });
        // 将卡牌图形框的两个信号关联到卡牌信息提示
        connect(handlbl[i],&mylabel::showprompt,[=](){
           // delete prompts;
           // prompts=nullptr;
           // showprompt(handcard.at(i).ID,this->x()+ui->mycard->x()+handlbl[i]->x(),this->y()+ui->mycard->y());
           showprompt(handcard.at(i).ID,100,200);
           qDebug()<<1;
        });
        connect(handlbl[i],&mylabel::hideprompt,[=](){
            // delete prompts;
            // prompts=nullptr;
                qDebug()<<2;
        });
        // 出牌
        connect(handlbl[i],&mylabel::labeldblclicked,[this,i](){
            delete prompts;
            prompts=nullptr;
            if(handcard.at(i).Type==1)//随从牌
            {
                if(handcard.at(i).Cost<=currentcrys)
                {
                    // 打出的牌都在最后一张, 所以用append
                    retinuecard.append(handcard.at(i));
                    if(handcard.at(i).Minion.Windfury) attacktime.append(2);
                    else attacktime.append(1);
                    currentcrys-=handcard.at(i).Cost;
                    handcard.remove(i);
                    retinuesetup();
                    refreshcrys();
                    handsetup();
                }
                else displayinfos("您的法力水晶不够！");
            }
            // else if  其余种类的牌尚未添加
        });
    }
    QByteArray buf;
    QDataStream out(&buf,QIODevice::WriteOnly);
    out<<REFRESH1<<rivalid<<(int)handcard.size()<<ini1;  // 将手牌容量和己方初始化状态传给对方
    _socket->write(buf);
}

void fight::retinuesetup()
{
    currentselect_retinue=-1;
    for(int j=0;j<10;j++)
    {
        if(retinuelbl[j]!=nullptr)
        {
            delete retinuelbl[j];
            retinuelbl[j]=nullptr;
        }
        selected_retinue[j]=false;
    }
    delete ui->myboard->layout();
    QHBoxLayout *m_lay=new QHBoxLayout;
    m_lay->setAlignment(Qt::AlignLeft);
    ui->myboard->setLayout(m_lay);
    for(int i=0;i<retinuecard.size();i++)
    {
        retinuelbl[i] = new retlabel;
        retinuelbl[i]->setFixedSize(ui->myboard->width()*0.095,ui->myboard->height()*0.92);
        m_lay->addWidget(retinuelbl[i]);
        retinuelbl[i]->drawcardpic(retinuecard.at(i).ID);
        retinuelbl[i]->SetBldAtk(retinuecard.at(i).Minion.Health,retinuecard.at(i).Minion.Attack); //显示攻击力与血量
        retinuelbl[i]->SetSleep(!retinuecard.at(i).Minion.Charge); // 设置休眠状态
        connect(retinuelbl[i],&retlabel::labelclicked,[this,i](){
           if(!retinuecard.at(i).Minion.Charge){ // 休眠
               displayinfos("卡牌["+QString::fromStdString(retinuecard[i].Name)+"]休眠中，无法发动攻击！");
               currentselect_retinue=-1;
           }
           else{ // 攻击
            if(selected_retinue[i])
            {
                currentselect_retinue=-1;
                retinuelbl[i]->selected(selected_retinue[i]);
                selected_retinue[i]=!selected_retinue[i];
            }
            else
            {
                // 解除手牌选中状态
                if(currentselect_hand!=-1)
                {
                    selected_hand[currentselect_hand]=!selected_hand[currentselect_hand];
                    handlbl[currentselect_hand]->setFrameShape(QFrame::NoFrame);
                    handlbl[currentselect_hand]->setStyleSheet("");
                    currentselect_hand=-1;
                }
                // 解除随从选中状态
                if(currentselect_retinue!=-1)
                {
                    retinuelbl[currentselect_retinue]->selected(selected_retinue[currentselect_retinue]);
                    selected_retinue[currentselect_retinue]=!selected_retinue[currentselect_retinue];
                }
                // 可攻击次数判断
                if(attacktime.at(i)==0)
                {
                    displayinfos("卡牌["+QString::fromStdString(retinuecard[i].Name)+"]该回合攻击次数已使用完！");
                    currentselect_retinue=-1;
                }
                else
                {
                    currentselect_retinue=i;
                    retinuelbl[i]->selected(selected_retinue[i]);
                    selected_retinue[i]=!selected_retinue[i];
                }
            }
           }
        });
        // 将卡牌图形框的两个信号关联到卡牌信息提示
        connect(retinuelbl[i],&retlabel::showprompt,[=](){
            /*delete prompts;
            prompts=nullptr;
            showprompt(retinuecard.at(i).ID,this->x()+ui->myboard->x()+retinuelbl[i]->x(),this->y()+ui->myboard->y());*/
             showprompt(retinuecard.at(i).ID,0,0);
             qDebug()<<3;
        });
        connect(retinuelbl[i],&retlabel::hideprompt,[=](){
         /*   delete prompts;
            prompts=nullptr;*/
            qDebug()<<4;
        });
    }
    sendretref();
}

void fight::rivalretsetup()
{
    // currentseletion_rivalret = -1;
    for(int j=0;j<10;j++)
    {
        if(rivalretlbl[j]!=nullptr)
        {
            delete rivalretlbl[j];
            rivalretlbl[j]=nullptr;
        }
        selected_rivalret[j]=false;
    }
    delete ui->rivalboard->layout();
    QHBoxLayout *m_lay=new QHBoxLayout;
    m_lay->setAlignment(Qt::AlignLeft);
    ui->rivalboard->setLayout(m_lay);
    for(int i=0;i<rivalretcard.size();i++)
    {
        rivalretlbl[i] = new retlabel;
        rivalretlbl[i]->setFixedSize(ui->rivalboard->width()*0.095,ui->rivalboard->height()*0.92);
        m_lay->addWidget(rivalretlbl[i]);
        rivalretlbl[i]->drawcardpic(rivalretcard.at(i).ID);
        rivalretlbl[i]->SetBldAtk(rivalretcard.at(i).Minion.Health,rivalretcard.at(i).Minion.Attack);
        connect(rivalretlbl[i],&retlabel::labelclicked,[this,i](){
            if(currentselect_hand==-1&&currentselect_retinue==-1); // 如果没选中过己方随从或手牌，不作反应
            else
            {
                if(currentselect_retinue!=-1)//如果是已打出的随从发起进攻
                {
                    if(retinuecard.at(currentselect_retinue).Minion.Charge)
                    {
                        bool istaunt=false;
                        for(int j=0;j<rivalretcard.count();j++)
                        {
                            if(rivalretcard.at(j).Minion.Taunt&&!rivalretcard.at(j).Minion.Stealth)//有嘲讽属性且不在潜行状态
                            {
                                istaunt=true;
                                break;
                            }
                        }
                        if(istaunt&&!rivalretcard.at(i).Minion.Taunt)
                            displayinfos("对方有嘲讽卡牌，请先攻击有嘲讽技能的随从！");
                        else if(rivalretcard.at(i).Minion.Stealth)
                            displayinfos(QString::fromStdString(rivalretcard[i].Name)+"为潜行卡牌，无法被攻击。");
                        else{
                            retinuecard[currentselect_retinue].Minion.Health-=rivalretcard.at(i).Minion.Attack;
                            if(rivalretcard[i].Minion.DivineShield) //若有圣盾
                                rivalretcard[i].Minion.DivineShield=false;//不扣血,圣盾解除
                            else rivalretcard[i].Minion.Health-=retinuecard.at(currentselect_retinue).Minion.Attack;//扣血
                            if(retinuecard[currentselect_retinue].Minion.Stealth)//若为潜行卡牌发动进攻
                                retinuecard[currentselect_retinue].Minion.Stealth=false;//解除潜行
                            attacktime[currentselect_retinue]-=1;
                            QVector<QString> tempinf;
                            displayinfos("我方的["+QString::fromStdString(retinuecard[currentselect_retinue].Name)+"]攻击了对方的["
                                         +QString::fromStdString(rivalretcard[i].Name)+"]!");
                            tempinf.append("我方的["+QString::fromStdString(rivalretcard[i].Name)+"]受到了对方["
                                           +QString::fromStdString(retinuecard[currentselect_retinue].Name)+"]的攻击!");
                            int infcnt=1; // 消息条目计数
                            if(retinuecard.at(currentselect_retinue).Minion.Health<=0)
                            {
                                displayinfos("我方的["+QString::fromStdString(retinuecard[currentselect_retinue].Name)+"]战死了");
                                tempinf.append("对方的["+QString::fromStdString(retinuecard[currentselect_retinue].Name)+"]战死了");
                                infcnt++;
                                retinuecard.remove(currentselect_retinue);
                                attacktime.remove(currentselect_retinue);
                            }
                            if(rivalretcard.at(i).Minion.Health<=0)
                            {
                                displayinfos("对方的["+QString::fromStdString(rivalretcard[i].Name)+"]战死了");
                                tempinf.append("我方的["+QString::fromStdString(rivalretcard[i].Name)+"]战死了");
                                infcnt++;
                                rivalretcard.remove(i);
                                delete prompts;
                                prompts=nullptr;
                            }
                            // TODO: 此处考虑限制消息条数；消息生成或可由服务端完成？
                            sendrivalretref();
                            QByteArray buf1;
                            QDataStream out1(&buf1,QIODevice::WriteOnly);
                            out1<<REFRESHINFO<<rivalid<<(int)tempinf.size()<<tempinf;
                            _socket->write(buf1);
                        }
                        retinuesetup();
                        rivalretsetup();
                    }
                    else displayinfos("该卡牌现处于休眠状态,无法发起进攻!");
                }
                // 如果是手牌中的法术直接攻击
                else if(currentselect_hand!=-1)
                {
                    // 手牌中选中的是随从类或武器类，不作反应
                    if(handcard[currentselect_hand].Type==1||handcard[currentselect_hand].Type==2);
                    // 手牌中选中的是法术类卡牌
                    else if(handcard[currentselect_hand].Type==3)
                    {
                        // 目前暂无法术牌，故暂未实现
                    }
                }
            }
        });
        // 将卡牌图形框的两个信号关联到卡牌信息提示
       connect(rivalretlbl[i],&retlabel::showprompt,[=](){
           /*  delete prompts;
            prompts=nullptr;
            showprompt(rivalretcard.at(i).ID,this->x()+ui->rivalboard->x()+rivalretlbl[i]->x(),this->y()+ui->rivalboard->y());*/
           showprompt(rivalretcard.at(i).ID,0,0);
           qDebug()<<5;
        });
        connect(rivalretlbl[i],&retlabel::hideprompt,[=](){
          //  delete prompts;
          //  prompts=nullptr;
            qDebug()<<6;
        });
    }
}

void fight::heroattack()
{
    if(currentselect_hand==-1&&currentselect_retinue==-1); // 如果没选中过己方随从或手牌，不作反应
    else
    {
        QByteArray buf1;
        QDataStream out1(&buf1,QIODevice::WriteOnly);
        out1<<REFRESHINFO<<rivalid;
        QVector<QString> tempinf;
        if(currentselect_retinue!=-1)//如果是已打出的随从发起进攻
        {
            bool istaunt=false;
            for(int i=0;i<rivalretcard.count();i++)
            {
                if(rivalretcard.at(i).Minion.Taunt&&!rivalretcard.at(i).Minion.Stealth)
                {
                    istaunt=true;
                    break;
                }
            }
            if(istaunt) displayinfos("对方有嘲讽卡牌，无法对英雄发起进攻！");
            else
            {
                if(retinuecard[currentselect_retinue].Minion.Stealth)//若为潜行卡牌发动进攻
                    retinuecard[currentselect_retinue].Minion.Stealth=false;//解除潜行
                rivalheroblood-=retinuecard.at(currentselect_retinue).Minion.Attack;
                displayinfos("我方的["+QString::fromStdString(retinuecard.at(currentselect_retinue).Name)+"]攻击了对方的英雄!");
                tempinf.append("我方的英雄受到了["+QString::fromStdString(retinuecard.at(currentselect_retinue).Name)+"]的攻击!");
                out1<<(int)tempinf.size()<<tempinf;
                _socket->write(buf1);
                attacktime[currentselect_retinue]-=1;
            }
            retinuesetup();
        }
        else if(currentselect_hand!=-1)//如果是手牌中的法术直接攻击
        {
            //判断类型
            if(handcard[currentselect_hand].Type==1||handcard[currentselect_hand].Type==2);
            else if(handcard[currentselect_hand].Type==3)
            {
                // 未加入此种类型卡牌, 暂且略去
            }
        }
        refreshcrys();
        refreshherobld();
    }
}

void fight::sendretref()
{
    QByteArray buf;
    QDataStream out(&buf,QIODevice::WriteOnly);
    out<<REFRESH2<<rivalid<<(int)retinuecard.size();
    for(int i=0;i<retinuecard.size();i++)
    {
        out<<retinuecard.at(i).ID<<retinuecard.at(i).Cost<<retinuecard.at(i).Hero
          <<QString::fromStdString(retinuecard.at(i).Name)<<retinuecard.at(i).Rarity
         //<<QString::fromStdString(retinuecard.at(i).Description)<<retinuecard.at(i).Type;
            <<retinuecard.at(i).Type;
        if(retinuecard.at(i).Type==1)
        {
            out<<retinuecard.at(i).Minion.Taunt<<retinuecard.at(i).Minion.Charge
              <<retinuecard.at(i).Minion.Frozen<<retinuecard.at(i).Minion.Stealth
             <<retinuecard.at(i).Minion.Windfury<<retinuecard.at(i).Minion.DivineShield
            <<retinuecard.at(i).Minion.Attack<<retinuecard.at(i).Minion.MaxAttack
            <<retinuecard.at(i).Minion.Health<<retinuecard.at(i).Minion.MaxHealth;
        }
        else if(retinuecard.at(i).Type==2)
        {
            out<<retinuecard.at(i).Weapon.Attack<<retinuecard.at(i).Weapon.Durability;
        }
    }
    _socket->write(buf);
}

void fight::sendrivalretref()
{
    QByteArray buf;
    QDataStream out(&buf,QIODevice::WriteOnly);
    out<<REFRESH5<<rivalid<<(int)rivalretcard.size();
    for(int i=0;i<rivalretcard.size();i++)
    {
        out<<rivalretcard.at(i).ID<<rivalretcard.at(i).Cost<<rivalretcard.at(i).Hero
          <<QString::fromStdString(rivalretcard.at(i).Name)<<rivalretcard.at(i).Rarity
        // <<QString::fromStdString(rivalretcard.at(i).Description)<<rivalretcard.at(i).Type;
            <<rivalretcard.at(i).Type;
        if(rivalretcard.at(i).Type==1)
        {
            out<<rivalretcard.at(i).Minion.Taunt<<rivalretcard.at(i).Minion.Charge
              <<rivalretcard.at(i).Minion.Frozen<<rivalretcard.at(i).Minion.Stealth
             <<rivalretcard.at(i).Minion.Windfury<<rivalretcard.at(i).Minion.DivineShield
            <<rivalretcard.at(i).Minion.Attack<<rivalretcard.at(i).Minion.MaxAttack
            <<rivalretcard.at(i).Minion.Health<<rivalretcard.at(i).Minion.MaxHealth;
        }
        else if(rivalretcard.at(i).Type==2)
        {
            out<<rivalretcard.at(i).Weapon.Attack<<rivalretcard.at(i).Weapon.Durability;
        }
    }
    _socket->write(buf);
}
/*原悬浮窗设计暂时作废
void fight::showprompt(int promptnum,int x,int y)
{
    prompts=new QLabel;
    prompts->setWindowFlags( Qt::WindowStaysOnTopHint
                             |Qt::FramelessWindowHint
                          //| Qt::WindowDoesNotAcceptFocus
                          | Qt::Tool
                          | Qt::X11BypassWindowManagerHint);
    prompts->setAttribute(Qt::WA_TransparentForMouseEvents);
    prompts->setFixedSize(307,458);
    prompts->setAlignment(Qt::AlignCenter);
    QPixmap pix;
    QString pixname;
    pixname = QString::fromStdString(":1/pic/")+QString::number(promptnum)+QString::fromStdString(".png");
    bool ret = pix.load(pixname);
    if(!ret)
    {
        QMessageBox::information(prompts,"提示","图片加载失败!");
        return;
    }
    prompts->setPixmap(pix.scaled(prompts->width(),prompts->height(),Qt::KeepAspectRatio));
    prompts->move(x-300,y-30);
    prompts->show();
}
*/
void fight::showprompt(int promptnum,int x,int y)
{
    QPixmap pix,pix1;
    QString pixname;
    pixname = QString::fromStdString(":1/pic/")+QString::number(promptnum)+QString::fromStdString(".png");
    pix.load(pixname);
    pix1=pix.copy(pix.width()*0.1,pix.height()*0.57,pix.width()*0.8,pix.height()*0.37);
    ui->promptlabel->setPixmap(pix1.scaled(ui->promptlabel->width(),ui->promptlabel->height(),Qt::KeepAspectRatio));
    if(Allcard[promptnum].Type==1)
        ui->prompttext->setText("卡牌名："+QString::fromStdString(Allcard[promptnum].Name)
                            +"，费用："+QString::number(Allcard[promptnum].Cost)
                            +"\n最大场攻："+QString::number(Allcard[promptnum].Minion.MaxAttack)
                            +"，最大生命："+QString::number(Allcard[promptnum].Minion.MaxHealth));
}
// 抽卡与疲劳
void fight::drawcard(int num)
{
    int i=0;
    bool tired=false;
    bool more=false;
    for(i=0;i<num;i++)
    {
        if(depositcard.size()==0)
        {
            tired=true;
            break;
        }
        if(handcard.size()==10)
        {
            more=true;
            displayinfos("您的手牌已达到10张,之后抽出的卡牌无法置入手牌!");
            break;
        }
        handcard.append(depositcard.pop());
    }
    for(int j=i;j<num;j++)
    {
        if(tired)
        {
            myheroblood-=tiredhurt;
            displayinfos("您受到了"+QString::number(tiredhurt)+"点疲劳伤害！");
            refreshherobld();
            tiredhurt++;
        }
        if(!tired&&more)
        {
            if(depositcard.size()==0)
            {
                tired=true;
                break;
            }
            depositcard.pop();
            displayinfos("您的手牌已达到10张,之后抽出的卡牌无法置入手牌!");
        }
    }
    handsetup();
}

void fight::displayinfos(QString content)
{
    infos[infocount%6]=QString::number(infocount+1)+"."+content;
    ui->information->setText("滚动信息提示：\n"+infos[0]+"\n"+infos[1]+"\n"+infos[2]+"\n"+infos[3]+"\n"
            +infos[4]+"\n"+infos[5]+"\n");
    ++infocount;
}
// 更新己方及对方英雄血量
void fight::refreshherobld()
{
    ui->myherobld->setText("当前血量"+QString::number(myheroblood));
    ui->rivalherobld->setText("当前血量"+QString::number(rivalheroblood));
    QByteArray buf;
    QDataStream out(&buf,QIODevice::WriteOnly);
    out<<REFRESH3<<myheroblood<<rivalheroblood<<rivalid;
    _socket->write(buf);
    if(rivalheroblood<=0)
    {
        QByteArray buf1;
        QDataStream out1(&buf1,QIODevice::WriteOnly);
        out1<<WIN<<myid<<rivalid;
        _socket->write(buf1);
        _timer.stop();
        QMessageBox::information(this,"提示","恭喜您战胜了对手");
        emit chooseSceneBack();
    }
}
// 更新己方法力水晶
void fight::refreshcrys()
{
    ui->mycrystal->setText("法力水晶"+QString::number(currentcrys)+"/"+QString::number(crystal));
    QByteArray buf;
    QDataStream out(&buf,QIODevice::WriteOnly);
    out<<REFRESH4<<currentcrys<<crystal<<rivalid;
    _socket->write(buf);
}

fight::~fight()
{
    delete ui;
}
// 以下是信号函数
// 认输按钮的信号函数
void fight::on_lose_clicked()
{
    QByteArray buf;
    QDataStream out(&buf,QIODevice::WriteOnly);
    out<<QUITGAME<<myid<<rivalid;
    _socket->write(buf);
    delete prompts;
    prompts=nullptr;
    QMessageBox::information(this,"提示","很遗憾，您战败了。");
    emit chooseSceneBack();
}
// 结束回合按钮的信号函数
void fight::on_endrnd_clicked()
{
    QByteArray buf;
    QDataStream out(&buf,QIODevice::WriteOnly);
    //如果是己方回合
    if(turn)
    {
        out<<ENDROUND<<rivalid;
        _socket->write(buf);
        ui->endrnd->setEnabled(false);
        ui->endrnd->setText("对手回合");
        turn=false;
        ui->timebar->hide();
        _timer.stop();
        disconnect(&_timer,&QTimer::timeout,0,0);
        for(int i=0;i<handcard.size();i++)
        {
            disconnect(handlbl[i],&mylabel::labelclicked,0,0);
            disconnect(handlbl[i],&mylabel::labeldblclicked,0,0);
        }
        for(int i=0;i<retinuecard.size();i++)
        {
            disconnect(retinuelbl[i],&retlabel::labelclicked,0,0);
        }
        for(int i=0;i<rivalretcard.size();i++)
        {
            disconnect(rivalretlbl[i],&retlabel::labelclicked,0,0);
        }
        disconnect(ui->rivalherolbl,&mylabel::labelclicked,0,0);
        currentselect_hand=-1;
        currentselect_retinue=-1;
    }
}

void fight::timerslot()
{
    _timecount--;
    ui->timebar->setValue(_timecount);
    if(_timecount==0) emit ui->endrnd->clicked();
}
