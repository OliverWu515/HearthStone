#ifndef FIGHT_H
#define FIGHT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <deck.h>
#include <card.h>
#include <firstchoose.h>
#include <QStack>
#include <QVector>
#include <retlabel.h>
#include <QTimer>

namespace Ui {
class fight;
}
// 向服务器传输的信号类型,只能在此定义一次,否则出现多重定义
enum DataType
{
    GAMESTART0 = 256, // 发送：向服务端发起配对请求；接收：服务端发来配对消息，接下来进入对战页面
    GAMESTART1, // 发送：向服务端发起配对请求；接收：服务端发来配对消息，接下来进入对战页面
    NOPLAYER, // 无玩家可供匹配；不能由客户端发送
    USERCONN, // 连接服务端成功；不能由客户端发送
    REFRESH1, // 发送：发送己方卡牌数量；接收：更新对方卡牌数量，兼具传输初始化标志功能
    REFRESH2, // 发送：发送己方随从信息给对手；接收：接收对方随从信息
    REFRESH3, // 发送或接收：更新血量
    REFRESH4, // 发送：向对方更新自己的法力水晶数；接收：接受并更新对方的法力水晶数
    REFRESH5, // 发送：向对方更新对方随从信息（例如己方攻击了对方随从后）；接收：更新己方随从信息
    REFRESHINFO,  // 向对方发送消息，例如对方随从被攻击等
    QUITGAME, // 发送：认输（掉线由服务端处理）；接收：对方认输或掉线
    SERVERCLOSE, // 暂未做实现
    SERVERFULL, // 接收：服务器已满；不能由客户端发送
    TIMEOUT, // 暂未做实现
    RANKLIST, // 暂未做实现
    WIN, // 发送：己方赢；接收：对手赢
    ENDROUND, // 发送：结束己方回合；接收：开始己方回合
    SETUP // 发送：将己方玩家名、对方编号和己方英雄名传给服务器；接收：获取对手信息并初次抽牌
};

class fight : public QMainWindow
{
    Q_OBJECT

public:
    explicit fight(QWidget *parent = nullptr);
    ~fight();
    void fightsetup(QString myname,QTcpSocket *_socket,int myid,int rivalid,deck newdeck);

signals:
    void chooseSceneBack();

private slots:
    void on_lose_clicked();

    void on_endrnd_clicked();
    void timerslot();

private:
    void slotGetServerData();
    Ui::fight *ui;
    QTcpSocket *_socket;//自己的套接字
    int myid;//己方编号，从0开始
    int rivalid;//对手编号，从0开始
    CARD Allcard[MaxCard+1];
    deck mydeck;//卡组信息
    bool first;//是否先手
    bool turn=false;//是否为己方回合
    // 己方与对方准备好的时机可能不同，故需两个变量
    bool ini1=false;//己方允许初始化标志
    bool ini2=false;//对方允许初始化标志
    void initialize();

    int round=1;//轮数
    int crystal;//总水晶数（上限）
    int currentcrys;//现有水晶数量
    int rivalcrys;//对手水晶上限
    int currentrivalcrys;//对手现有水晶数量
    void refreshcrys();

    int myheroblood=30;//我方英雄血量
    int rivalheroblood=30;//对方英雄血量
    void heroattack();//攻击对方英雄
    void refreshherobld();//刷新英雄血量
    //我方英雄技能，暂未做实现
    //对方英雄技能，暂未做实现

    firstchoose *fcscene = nullptr; //对战刚开始的选择画面
    QStack<CARD> depositcard; // 牌库（初始时为整个卡组）

    QVector<CARD> handcard; // 手牌信息
    mylabel *handlbl[10]={nullptr};//手牌显示
    void handsetup(); // 处理手牌有关的显示部分
    bool selected_hand[10]={false}; // 手牌是否被选
    int currentselect_hand=-1; // 当前选择的手牌号

    QVector<CARD> retinuecard; // 随从（打出的手牌）信息
    retlabel *retinuelbl[10]={nullptr};//随从显示框
    void retinuesetup();//处理己方随从有关的显示部分
    bool selected_retinue[10]={false};//己方随从是否被选
    QVector<uint8_t> attacktime;//是否已经攻击过了
    int currentselect_retinue=-1;//当前选择的随从号，随从即已经打出的手牌
    void sendretref();// 发送己方随从信息给对手

    QLabel *prompts=nullptr;//显示卡牌信息用
    void showprompt(int promptnum,int x,int y);//显示卡牌信息

    QVector<CARD> rivalretcard; // 对手随从信息
    retlabel *rivalretlbl[10]={nullptr};//对手随从显示框
    void rivalretsetup();//处理对方随从有关的显示部分
    bool selected_rivalret[10]={false};//(对手)随从是否可被选择
    int currentseletion_rivalret;//当前选择的(对方)随从
    void sendrivalretref();// 更新对方随从信息给对手

    void drawcard(int num);//抽卡
    int tiredhurt=1;//疲劳伤害
    QString infos[6]={""};//总6条消息
    int infocount=0;
    void displayinfos(QString content);

    QTimer _timer;
    int _timecount=100;
};

#endif // FIGHT_H
