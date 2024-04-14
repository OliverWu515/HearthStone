#include "playerchoose.h"
#include "ui_playerchoose.h"
#include <card.h>
#include <mylabel.h>
#include <QMessageBox>
#include <QInputDialog>
#include <QMessageBox>
#include <QScreen>
#include <QRect>

playerchoose::playerchoose(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::playerchoose)
{
    ui->setupUi(this);
    //showFullScreen();
    //获取窗口分辨率
    QRect mRect;
    mRect = QGuiApplication::primaryScreen()->geometry();
    //最大长宽设为窗口长宽的80%
    setFixedSize(mRect.width()*0.8,mRect.height()*0.8);
    setWindowTitle("请选择卡组");
    setWindowIcon(QIcon(":/1/pic/logo_1.jpg"));
    ui->widget->setFixedWidth(this->width()*0.4);
    ui->player1frame->setFixedHeight(this->height()*0.6);
    ui->funcwidget->setFixedHeight(this->height()*0.32);
    ui->hint->setFixedHeight(20);
    this->selfsetup();
    //返回按钮设置
    connect(ui->playerchooseexit,&QPushButton::clicked,[=](){
        // if(_socket != nullptr && _socket->isOpen()){
        if(_socket != nullptr){
            disconnect(this->_socket,&QTcpSocket::disconnected,0,0);
            _socket->disconnectFromHost();
        }
        qDebug() << "返回主页面";
        //发出返回信号 主场景监听信号
        emit chooseSceneBack();
    });
    //初始选定按钮不可用
    if(ui->deckinf->currentRow()==-1)ui->player1select->setDisabled(true);
    ui->startgame->setDisabled(true);
    ui->playerchooseexit->setFixedHeight(this->height()*0.1);
    //一旦有卡组被选中则启用选定按钮
    connect(ui->deckinf,&QListWidget::itemClicked,[=](){
        ui->player1select->setEnabled(true);
    });
    ui->player1->setText("玩家1");
    //todo:限制输入字数,输入到一定字数截断
    QInputDialog *dialog1=new QInputDialog;
    //自定义玩家名
    connect(ui->player1,&mylabel::labelclicked,[=](){
        bool ok;
        QString titleprompt;
        titleprompt = dialog1->getText(this,"请设置卡组名","输入玩家1的名字(不超过24个字符)",QLineEdit::Normal,ui->player1->text(),&ok).left(24);
        if(ok&&!titleprompt.isEmpty())  ui->player1->setText(titleprompt);
    });
    //选定按钮设置
    ui->player1inf->setFont(QFont("华文楷体",16));
    ui->player1inf->setText("请做出选择……");
    ui->player1inf->setFixedHeight(64);
    ui->textBrowser->setFont(QFont("华文楷体",12));
    CARD TEMP[MaxCard+1];
    SetCard(TEMP);
    connect(ui->player1select,&QPushButton::clicked,[=](){
        int currentrow;
        currentrow=ui->deckinf->currentRow()+1;//获取当前行下标
        newdeck = ReadDeck(deckid[currentrow]);
        ui->player1inf->setText("选择了："+newdeck.Name+
                                "\n职业为："+GetHeroName(newdeck.Hero));
        ui->textBrowser->clear();
        ui->textBrowser->append("卡牌信息：");
        for(int i=1;i<=30;i++)
        {
            if(i<30&&newdeck.CardID[i]==newdeck.CardID[i+1])
            {
                ui->textBrowser->append(QString::fromStdString(TEMP[newdeck.CardID[i]].Name)+" (2张)");
                i++;
            }
            else ui->textBrowser->append(QString::fromStdString(TEMP[newdeck.CardID[i]].Name));
        }
        this->player1chosen=true;
        if(this->player1chosen&&starting) ui->startgame->setEnabled(true);
    });
    ui->IPLE->setInputMask("000.000.000.000;_");
    ui->PORTLE->setInputMask("0000;_");
    //以下两行测试用
    ui->IPLE->setText("127.0.0.1");
    ui->PORTLE->setText("8585");
}
//初始化时填充卡组条目
void playerchoose::selfsetup()
{
    ui->deckinf->clear();
    int totaldecknum=0;
    totaldecknum=GetDeckNum();
    items=totaldecknum;
    totaldecknum++;
    deck deck1[totaldecknum];
    int validdecknum=0;
    for(int i=1;i<totaldecknum;i++) deck1[i]=ReadDeck(i);
    for(int i=1;i<totaldecknum;i++)
    {
        if(deck1[i].Sum!=30)  continue;
        validdecknum++;
        item[validdecknum]=new QListWidgetItem;
        item[validdecknum]->setText(QString::number(validdecknum)+"  "+deck1[i].Name+
                                    " (职业："+GetHeroName(deck1[i].Hero)+")");
        ui->deckinf->addItem(item[validdecknum]);
        item[validdecknum]->setSizeHint(QSize(10,70));
        item[validdecknum]->setFont(QFont("华文楷体",14));
        deckid[validdecknum]=i;
    }
}

playerchoose::~playerchoose()
{
    delete ui;
}

void playerchoose::on_connectbtn_clicked()
{
    ui->connectbtn->setEnabled(false);
    _socket = new QTcpSocket(this);
    _socket->connectToHost(ui->IPLE->text(),ui->PORTLE->text().toInt());
    connect(_socket,&QTcpSocket::errorOccurred, this,[=](){
        QMessageBox::warning(this,"错误","连接时发生错误！");
        ui->displaylbl->setText("您还没有连接服务器！");
        ui->connectbtn->setEnabled(true);
        ui->startgame->setEnabled(false);
        starting=false;
    });
    connect(_socket,&QTcpSocket::readyRead, this,&playerchoose::slotGetServerData);
    connect(_socket,&QTcpSocket::disconnected,[=](){
        QMessageBox::warning(this,"警告","抱歉，您和服务器的连接断开！");
        ui->displaylbl->setText("您还没有连接服务器！");
        ui->connectbtn->setEnabled(true);
        ui->startgame->setEnabled(false);
        starting=false;
    });
}

void playerchoose::slotGetServerData()
{
    starting=true;
    if(this->player1chosen&&starting) ui->startgame->setEnabled(true);
    QDataStream in;
    in.setDevice(_socket);
    while(_socket && _socket->bytesAvailable())
    {
        int type;
        in>>type;

        switch(type)
        {
        case USERCONN:
            ui->displaylbl->setText("服务器连接成功！");
            break;
        case GAMESTART0: // 服务器发来了配对消息，接下来进入对战页面
        case GAMESTART1:
        {
            in>>rivalid>>myid;
         //   QMessageBox::information(this,"温馨提示",tr("您是%1号选手,成功匹配到了%2号对手").arg(mynum).arg(rivalnum));
            this->fightscenesetup(); // 对战初始化
        }
            break;
        case NOPLAYER:
            QMessageBox::information(this,"温馨提示","目前暂没有可供对战的玩家，请耐心等待！");
            break;
        case SERVERFULL:
            QMessageBox::information(this,"温馨提示","目前服务器已满，请耐心等待！");
            break;
        }
    }
}

void playerchoose::on_startgame_clicked()
{
    QMessageBox::information(this,"温馨提示","正在为您匹配对手，请稍候");
    QByteArray buf;
    QDataStream out(&buf,QIODevice::WriteOnly);
    out<<GAMESTART1; // 向服务器发起匹配请求
    _socket->write(buf);
}
// 对战页面建立
void playerchoose::fightscenesetup()
{
    fightscene=new fight;
    fightscene->show();
    this->hide();
    // 将套接字读取信息的信号函数与本页面解绑，以便对战页面重新绑定
    disconnect(_socket,&QTcpSocket::readyRead, this,&playerchoose::slotGetServerData);
    fightscene->fightsetup(ui->player1->text(),_socket,myid,rivalid,newdeck);
    // 对战界面发出返回信号时需要调用fightscenedelete函数
    connect(fightscene,&fight::chooseSceneBack,this,&playerchoose::fightscenedelete);
}
void playerchoose::fightscenedelete()
{
    delete fightscene;
    fightscene=nullptr;
    this->show();
    // 将套接字读取信息的信号函数与本页面绑定
    connect(_socket,&QTcpSocket::readyRead, this,&playerchoose::slotGetServerData);
}
