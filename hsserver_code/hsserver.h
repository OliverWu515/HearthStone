#ifndef HSSERVER_H
#define HSSERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

#define MAXCONNCOUNT 50

enum DataType
{
    GAMESTART0 = 256,
    GAMESTART1, // 游戏开始，进行匹配，并在表中更新对战双方信息
    NOPLAYER, // 无玩家可供匹配
    USERCONN, // 连接服务端成功
    REFRESH1, // 接收卡牌数量并转发
    REFRESH2, // 接收并转发随从变动
    REFRESH3, // 接收血量并转发
    REFRESH4, // 接收水晶数并转发
    REFRESH5, // 接收并转发随从变动，在服务端REFRESH2和REFRESH5是相同的
    REFRESHINFO, // 接收消息并转发
    QUITGAME, // 接收并转发一方认输消息，并在表中更新对战双方信息
    SERVERCLOSE, // 暂未做实现
    SERVERFULL, // 服务端已满
    TIMEOUT, // 暂未做实现
    RANKLIST, // 暂未做实现
    WIN, // 接收并转发，并在表中更新对战双方信息
    ENDROUND, // 接收并转发结束回合消息
    SETUP // 客户端已建立页面，服务端分配先后手并传输玩家名等
};
struct UserInfo
{
    QString name;
    int heroid;
    QTcpSocket* ptrSocket;//套接字
    bool read;//套接字是否可用
    bool setup=false;//是否已经建立页面
    //int rivalid=0;
};
QT_BEGIN_NAMESPACE
namespace Ui { class HsServer; }
QT_END_NAMESPACE

class HsServer : public QMainWindow
{
    Q_OBJECT

public:
    HsServer(QWidget *parent = nullptr);
    ~HsServer();
    void closeEvent(QCloseEvent *event);

private slots:
    void on_startserver_clicked();
    void slotCreateConnection();

private:
    Ui::HsServer *ui;
    QVector<uint16_t> GetAllTcpConnectionsPort();
    QVector<uint16_t> FindAvailableTcpPort(uint16_t begin, uint16_t end);
    QTcpServer _server;
    int _userCount=0;//服务器内用户个数
    UserInfo _userInfo[MAXCONNCOUNT];//各用户信息
    int updateInfo(int,int,bool);//更新列表
};
#endif // HSSERVER_H
