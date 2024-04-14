#include "hsserver.h"
#include "ui_hsserver.h"
#include <QDebug>
// #include <QStyleFactory>
// 操作系统API
#include <Windows.h>
#include <WinSock.h>
#include <QRegularExpression>
// #include <tcpmib.h>
#include <IPHlpApi.h>
#include <memory>
#include <algorithm>
#include <string.h>

#include <QHostInfo>
//端口号取值范围【0-65535】，其中1023以前预留给了常用应用程序,一般在1024之后取端口号
#define PORT_DOWN 8500	//起始端口号
#define PORT_UP 8600	//终止端口号

HsServer::HsServer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HsServer)
{
    ui->setupUi(this);
    // qDebug()<<QStyleFactory::keys();
    this->setFixedSize(this->size());
    setWindowTitle("简易炉石传说服务器端");
    //正则表达式限制输入
    QRegularExpression regPort = QRegularExpression("(85\\d{2})|(8600)");
    ui->portLE->setValidator(new QRegularExpressionValidator(regPort,this));
    for(int i=0; i<MAXCONNCOUNT; i++)
    {
        //_arrName[i] = "";
        _userInfo[i].read = false;
        _userInfo[i].ptrSocket = nullptr;
        // _ranklist[i] = i;
    }
}

// https://blog.csdn.net/flushhip/article/details/84840442
// 获取所有已占用的TCP端口号
QVector<uint16_t> HsServer::GetAllTcpConnectionsPort()
{
    QVector<uint16_t> ret;
    ULONG size = 0;
    GetTcpTable(NULL, &size, TRUE);
    std::unique_ptr<char[]> buffer(new char[size]);

    PMIB_TCPTABLE tcpTable = reinterpret_cast<PMIB_TCPTABLE>(buffer.get());
    if (GetTcpTable(tcpTable, &size, FALSE) == NO_ERROR)
        for (size_t i = 0; i < tcpTable->dwNumEntries; i++)
            ret.push_back(ntohs((uint16_t)tcpTable->table[i].dwLocalPort));
    std::sort(std::begin(ret), std::end(ret));
    return ret;
}

//查找可用的TCP端口
QVector<uint16_t> HsServer::FindAvailableTcpPort(uint16_t begin, uint16_t end)
{
    auto vec = GetAllTcpConnectionsPort();
    QVector<uint16_t> availablePortVector;
    int i = 0;
    //在端口区间检测端口是否在占用列表中，如果不在则表示当前的端口可用并返回
    for (uint16_t port = begin; port < end; ++port)
        if (!std::binary_search(std::begin(vec), std::end(vec), port))
            availablePortVector.insert(i++,port);
    return availablePortVector;
}

void HsServer::on_startserver_clicked()
{
    if(ui->portLE->text().toUInt()>=PORT_DOWN&&ui->portLE->text().toUInt()<=PORT_UP
            &&FindAvailableTcpPort(PORT_DOWN,PORT_UP).contains(ui->portLE->text().toUInt()))
    {
        bool ok = _server.listen(QHostAddress::Any,ui->portLE->text().toInt());
        if(ok)
        {
            ui->status->append("服务器成功地启动了监听");
            ui->startserver->setEnabled(false);
            connect(&_server,&QTcpServer::newConnection,this,&HsServer::slotCreateConnection);
        }
        else ui->status->append("启动监听失败");
    }
    else ui->status->append("启动监听失败,不在端口范围内或该端口已被占用,请重新输入");
}

void HsServer::slotCreateConnection()
{
    QTcpSocket* socket = _server.nextPendingConnection();
    if(_userCount >= MAXCONNCOUNT)
    {
        QByteArray buf;
        QDataStream out(&buf,QIODevice::WriteOnly);
        out<<SERVERFULL; // 服务器已满
        socket->write(buf);
        return;
    }

    for(int i=0; i<MAXCONNCOUNT; i++)
    {
        //如果某套接字是闲置的，那么把这个socket分配给该套接字，最后接有break(找到一个即退出循环)
        if(nullptr == _userInfo[i].ptrSocket)
        {
            _userInfo[i].ptrSocket = socket;
            _userInfo[i].read = false;
            _userCount++;

            QByteArray buf;
            QDataStream out(&buf,QIODevice::WriteOnly);
            out<<USERCONN<<_userInfo[i].name.toInt();
            _userInfo[i].ptrSocket->write(buf);
            ui->status->append(tr("%1号选手进入了服务器").arg(i+1));

            // 收到用户端信息时会产生readyread信号，服务端即开始处理信息
            connect(_userInfo[i].ptrSocket,&QTcpSocket::readyRead,[this,i](){
                int index=0;
                while(_userInfo[i].ptrSocket && _userInfo[i].ptrSocket->bytesAvailable())
                {
                    QDataStream in;
                    in.setDevice(_userInfo[i].ptrSocket);
                    int type;
                    in>>type;
                    // 根据消息类型作出响应
                    switch(type)
                    {
                    case GAMESTART0:
                    case GAMESTART1:
                    {
                        bool matching=false; // 正在匹配状态
                        _userInfo[i].read = true; // 可被连接状态
                        for(index=0; index<MAXCONNCOUNT; index++)
                        {
                            if(i!=index && _userInfo[index].ptrSocket && _userInfo[index].read)//如果匹配到了对手
                            {
                                matching=true; // 正在匹配状态解除
                                ui->status->append(tr("%1号和%2号开始了对局").arg(i+1).arg(index+1));
                                _userInfo[i].read = _userInfo[index].read = false;  // 可被连接状态解除(进入对局不能再连接其他用户)
                                updateInfo(i+1,index+1,false);

                                QByteArray buf1;
                                QDataStream out1(&buf1,QIODevice::WriteOnly);
                                out1<<GAMESTART0<<i<<index;//把双方编号发给被匹配者
                                _userInfo[index].ptrSocket->write(buf1);

                                QByteArray buf2;
                                QDataStream out2(&buf2,QIODevice::WriteOnly);
                                out2<<GAMESTART1<<index<<i;//把双方编号发给请求匹配者
                                _userInfo[i].ptrSocket->write(buf2);
                            }
                        }
                        if(!matching)
                        {
                            QByteArray buf1;
                            QDataStream out1(&buf1,QIODevice::WriteOnly);
                            out1<<NOPLAYER;  // 未能匹配到
                            _userInfo[i].ptrSocket->write(buf1);
                        }
                    }
                        break;
                    // 客户端已建立页面，服务端分配先后手
                    case SETUP:
                    {
                        in>>_userInfo[i].name;
                        in>>_userInfo[i].setup;
                        int rivalnumtemp;
                        in>>rivalnumtemp;
                        in>>_userInfo[i].heroid;
                        if(_userInfo[i].setup&&_userInfo[rivalnumtemp].setup)
                        {
                            srand(time(NULL));
                            bool randnum = rand()%2;

                            // 发送各自的先后手情况和对方的英雄名、玩家名
                            QByteArray buf1;
                            QDataStream out1(&buf1,QIODevice::WriteOnly);
                            out1<<SETUP<<_userInfo[rivalnumtemp].name<<randnum<<_userInfo[rivalnumtemp].heroid;
                            _userInfo[i].ptrSocket->write(buf1);

                            QByteArray buf2;
                            QDataStream out2(&buf2,QIODevice::WriteOnly);
                            out2<<SETUP<<_userInfo[i].name<<!randnum<<_userInfo[i].heroid;
                            _userInfo[rivalnumtemp].ptrSocket->write(buf2);
                            // 先后手、玩家名、英雄只同步一次
                            _userInfo[i].setup=_userInfo[rivalnumtemp].setup=false;
                        }
                    }
                        break;
                    case REFRESH1:
                    {
                        int rivalid;
                        in>>rivalid;
                        int cardsize;
                        in>>cardsize;
                        bool initialized;
                        in>>initialized;
                        QByteArray buf1;
                        QDataStream out1(&buf1,QIODevice::WriteOnly);
                        out1<<REFRESH1<<cardsize<<initialized;
                        _userInfo[rivalid].ptrSocket->write(buf1);
                    }
                        break;
                    case REFRESH2:
                    {
                        int rivalid;
                        in>>rivalid;
                        int size;
                        in>>size;
                        qDebug()<<size;
                        QByteArray buf1;
                        QDataStream out1(&buf1,QIODevice::WriteOnly);
                        out1<<REFRESH2<<size;
                        for(int i=0;i<size;i++)
                        {
                            // 此处abcd等对应各种卡牌属性，与客户端对应设计
                            int a,b,c,g;
                            QString d;
                            //QString f;
                            bool e;
                            //in>>a>>b>>c>>d>>e>>f>>g;
                            in>>a>>b>>c>>d>>e>>g;
                            //out1<<a<<b<<c<<d<<e<<f<<g;
                            out1<<a<<b<<c<<d<<e<<g;
                            qDebug()<<a<<b<<c<<d<<e<<g;
                            if(g==1)
                            {
                                bool h,i,j,k,l,m;
                                int n,o,p,q;
                                in>>h>>i>>j>>k>>l>>m>>n>>o>>p>>q;
                                out1<<h<<i<<j<<k<<l<<m<<n<<o<<p<<q;
                                qDebug()<<h<<i<<j<<k<<l<<m<<n<<o<<p<<q;
                            }
                            else if(g==2)
                            {
                                int n,o;
                                in>>n>>o;
                                out1<<n<<o;
                            }
                        }
                        _userInfo[rivalid].ptrSocket->write(buf1);
                    }
                        break;
                    case REFRESH3:
                    {
                        int r,m;
                        in>>r>>m;
                        int rivalid;
                        in>>rivalid;
                        QByteArray buf1;
                        QDataStream out1(&buf1,QIODevice::WriteOnly);
                        out1<<REFRESH3<<r<<m;
                        _userInfo[rivalid].ptrSocket->write(buf1);
                    }
                        break;
                    case REFRESH4:
                    {
                        // 前者是剩余法力水晶数，后者是法力水晶总数
                        int crys,totalcrys;
                        in>>crys>>totalcrys;
                        int rivalid;
                        in>>rivalid;
                        QByteArray buf1;
                        QDataStream out1(&buf1,QIODevice::WriteOnly);
                        out1<<REFRESH4<<crys<<totalcrys;
                        _userInfo[rivalid].ptrSocket->write(buf1);
                    }
                        break;
                    case REFRESH5:
                    {
                        int rivalid;
                        in>>rivalid;
                        int size;
                        in>>size;
                        QByteArray buf1;
                        QDataStream out1(&buf1,QIODevice::WriteOnly);
                        out1<<REFRESH5<<size;
                        for(int i=0;i<size;i++)
                        {
                            // 此处abcd等对应各种卡牌属性，与客户端对应设计
                            int a,b,c,g;
                            QString d;
                           // QString f;
                            bool e;
                            //in>>a>>b>>c>>d>>e>>f>>g;
                            in>>a>>b>>c>>d>>e>>g;
                            //out1<<a<<b<<c<<d<<e<<f<<g;
                            out1<<a<<b<<c<<d<<e<<g;
                            if(g==1)
                            {
                                bool h,i,j,k,l,m;
                                int n,o,p,q;
                                in>>h>>i>>j>>k>>l>>m>>n>>o>>p>>q;
                                out1<<h<<i<<j<<k<<l<<m<<n<<o<<p<<q;
                            }
                            else if(g==2)
                            {
                                int n,o;
                                in>>n>>o;
                                out1<<n<<o;
                            }
                        }
                        _userInfo[rivalid].ptrSocket->write(buf1);
                    }
                        break;
                    case REFRESHINFO:
                    {
                        int rivalid;
                        in>>rivalid;
                        int cnt;
                        in>>cnt;
                        QVector<QString> st;
                        in>>st;
                        QByteArray buf1;
                        QDataStream out1(&buf1,QIODevice::WriteOnly);
                        out1<<REFRESHINFO<<cnt<<st;
                        _userInfo[rivalid].ptrSocket->write(buf1);
                    }
                        break;
                    case ENDROUND:
                    {
                        int rivalid;
                        in>>rivalid;
                        QByteArray buf1;
                        QDataStream out1(&buf1,QIODevice::WriteOnly);
                        out1<<ENDROUND;
                        _userInfo[rivalid].ptrSocket->write(buf1);
                    }
                        break;
                    case QUITGAME:
                    {
                        int i1,i2;
                        in>>i1>>i2;
                        QByteArray buf1;
                        QDataStream out1(&buf1,QIODevice::WriteOnly);
                        out1<<QUITGAME<<false;
                        _userInfo[i2].ptrSocket->write(buf1);
                        _userInfo[i1].read=false;
                        _userInfo[i2].read=false;
                        updateInfo(i1+1, 0,true);
                    }
                        break;
                    case WIN:
                    {
                        int i1,i2;
                        in>>i1>>i2;
                        ui->status->append(tr("%1号选手战胜了%2号选手").arg(i1+1).arg(i2+1));
                        QByteArray buf1;
                        QDataStream out1(&buf1,QIODevice::WriteOnly);
                        out1<<WIN;
                        _userInfo[i2].ptrSocket->write(buf1);
                        _userInfo[i1].read=false;
                        _userInfo[i2].read=false;
                        updateInfo(i1+1, 0,true);
                    }
                        break;
                    }
                }
            });
            //断开时操作
            connect(_userInfo[i].ptrSocket,&QTcpSocket::disconnected,[this,i](){
                int winnum = updateInfo(i+1, 0, true); //找出胜者，在函数里面，还把胜者与负者一起踢出房间
                if(winnum!=-1 && _userInfo[winnum].ptrSocket)
                {
                    QByteArray buf;
                    QDataStream out(&buf,QIODevice::WriteOnly);
                    out<<QUITGAME<<true;
                    _userInfo[winnum].ptrSocket->write(buf);
                }
                //重新分配这个选手号
                ui->status->append(tr("%1号选手离开了服务器").arg(i+1));
                _userInfo[i].ptrSocket->close();
                _userInfo[i].ptrSocket = nullptr;
                _userInfo[i].read = false;
            });
            break;
        }
    }
}


/**
 * 更新用户信息
 * remove 为 false 时，更新对局者信息到右侧的列表中
 * remove 为 true 时，代表对局结束，要移除对局者的信息
 */
int HsServer::updateInfo(int a, int b, bool remove)
{
    if(remove)
    {
        for(int i=0; i<ui->userstate->rowCount(); i++)
        {
            // 根据选手a的编号找出他与对手b的对局，然后把他们移出对决房间。找到一个即可(提高运行效率)
            if(a == ui->userstate->item(i,0)->text().toInt())
            {
                int ret =  ui->userstate->item(i,1)->text().toInt()-1;
                int other = ui->userstate->item(i,0)->text().toInt()-1;
                _userInfo[ret].read = false;
                _userInfo[other].read = false;
                ui->userstate->removeRow(i);
                return ret;
            }
            if(a == ui->userstate->item(i,1)->text().toInt())
            {
                int ret =  ui->userstate->item(i,0)->text().toInt()-1;
                int other = ui->userstate->item(i,1)->text().toInt()-1;
                _userInfo[ret].read = false;
                _userInfo[other].read = false;
                ui->userstate->removeRow(i);
                return ret;
            }
        }
    }
    else
    {
        QTableWidgetItem* item1 = new QTableWidgetItem(QString::number(a));
        QTableWidgetItem* item2 = new QTableWidgetItem(QString::number(b));
        int row = ui->userstate->rowCount();
        ui->userstate->setRowCount(row+1);
        ui->userstate->setItem(row,1,item1);
        ui->userstate->setItem(row,0,item2);
    }
    return -1;
}

void HsServer::closeEvent(QCloseEvent *event)
{
    for(int i=0; i<MAXCONNCOUNT; i++)
    {
        if(_userInfo[i].ptrSocket!=nullptr){
            _userInfo[i].ptrSocket->disconnectFromHost();
            _userInfo[i].ptrSocket = nullptr;
        }
    }
}

HsServer::~HsServer()
{
    delete ui;
}
