#include "deck_and_heros.h"
#include "ui_deck_and_heros.h"
#include <QPushButton>
#include <QTimer>
#include <QListWidget>
#include <QListWidgetItem>
#include <deck.h>
#include<QMessageBox>
#include <QInputDialog>
#include <card.h>

deck_and_heros::deck_and_heros(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::deck_and_heros)
{
    ui->setupUi(this);
    showFullScreen();
    setWindowTitle("卡组编辑页面");
    setWindowIcon(QIcon(":/1/pic/logo_1.jpg"));
    //右侧菜单填充
    this->selfsetup();
    ui->widget->setFixedWidth(this->width()*0.7);
    ui->widget->setFixedHeight(this->height()*0.97);
    //初始化职业按钮
    selectwidget *heropages[2];
    for (int i=0;i<2;i++)
    {
        heropages[i] = new selectwidget;
        ui->stackedWidget->addWidget(heropages[i]);
        if(i==0) heropages[i]->setdecks(6,1);
        else
        {
            heropages[i]->setdecks(3,7);
            heropages[i]->lessbutton(3);
        }
    }
    //翻页按钮样式设置
    ui->lastpage->setStyleSheet("background:rgba(0,0,0,0)");
    ui->nextpage->setStyleSheet("background:rgba(0,0,0,0)");
    ui->lastpage->setIcon(QIcon(":/1/pic/leftarrow.png"));
    ui->nextpage->setIcon(QIcon(":/1/pic/rightarrow.png"));
    //关联切换页面操作及页码显示框
    connect(ui->lastpage,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
    });
    connect(ui->nextpage,&QPushButton::clicked,[=](){
        ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
    });
    connect(ui->stackedWidget,&QStackedWidget::currentChanged,[=](){
        ui->pagenum->setText("第"+QString::number(ui->stackedWidget->currentIndex()+1)+"页，共"+
                             QString::number(ui->stackedWidget->count())+"页");
    });
    ui->pagenum->setText("第"+QString::number(ui->stackedWidget->currentIndex()+1)+"页，共"+
                         QString::number(ui->stackedWidget->count())+"页");
    //设置按钮文字
    ui->editdeck->setText("编辑卡组");
    ui->newdeck->setText("新建卡组");
    ui->renamedeck->setText("重命名");
    ui->deletebtn->setText("删除卡组");
    ui->returntolast->setText("返回主页面");
    //新建按钮设置
    connect(ui->newdeck,&QPushButton::clicked,[=](){
        ui->prompt->setText("请选择英雄");
        for(int i=0;i<9;i++) heropages[i/6]->buttonlist[i%6]->setEnabled(true);
    });
    for(int i=0;i<9;i++){
        connect(heropages[i/6]->buttonlist[i%6],&QToolButton::clicked,[=](){
            chosen=i+1;
            ui->prompt->setText("");
            for(int i=0;i<9;i++)  heropages[i/6]->buttonlist[i%6]->setEnabled(false);
            this->newdecksetup();
        });
    }
    //删除按钮设置
    connect(ui->deletebtn,&QPushButton::clicked,this,&deck_and_heros::itemdeleted);
    connect(ui->deletebtn,&QPushButton::clicked,[=](){
        ui->deletebtn->setDisabled(true);
    });
    //编辑按钮设置
    connect(ui->editdeck,&QPushButton::clicked,this,&deck_and_heros::choosecardsetup);
    connect(ui->editdeck,&QPushButton::clicked,[=](){
        ui->editdeck->setDisabled(true);
    });
    //初始删除/编辑/重命名按钮不可用
    if(ui->deckinf->currentRow()==-1)ui->deletebtn->setDisabled(true);
    if(ui->deckinf->currentRow()==-1)ui->editdeck->setDisabled(true);
    if(ui->deckinf->currentRow()==-1)ui->renamedeck->setDisabled(true);
    //一旦有卡组被选中则启用删除/编辑按钮
    connect(ui->deckinf,&QListWidget::itemClicked,[=](){
        ui->deletebtn->setEnabled(true);
        ui->editdeck->setEnabled(true);
        ui->renamedeck->setEnabled(true);
    });
    //重命名按钮设置
    connect(ui->renamedeck,&QPushButton::clicked,this,&deck_and_heros::renamedeck);
    //返回按钮设置
    connect(ui->returntolast,&QPushButton::clicked,[=](){
        qDebug() << "返回主页面";
        //发出返回信号 主场景监听信号
        emit chooseSceneBack();
        SetDeckNum(items);
    });
}
//初始化时填充条目
void deck_and_heros::selfsetup()
{
    ui->deckinf->clear();
    int totaldecknum=0;
    totaldecknum=GetDeckNum();
    items=totaldecknum;
    totaldecknum++;
    deck deck1[totaldecknum];
    qDebug()<<totaldecknum;
    for(int i=1;i<totaldecknum;i++) deck1[i]=ReadDeck(i);
    for(int i=1;i<totaldecknum;i++)
    {
        item[i]=new QListWidgetItem;
        item[i]->setText(QString::number(i)+"  "+deck1[i].Name+
                         "\n(共"+QString::number(deck1[i].Sum)+"张) (职业："+GetHeroName(deck1[i].Hero)+")");
        ui->deckinf->addItem(item[i]);
        item[i]->setSizeHint(QSize(10,70));
        item[i]->setFont(QFont("华文楷体",14));
    }
}
//删除条目
void deck_and_heros::itemdeleted()
{
    int currentrow;
    currentrow=ui->deckinf->currentRow()+1;//获取当前行下标
    QMessageBox *msgbox=new QMessageBox;
    if(msgbox->information(this,"请确认","确定要删除吗？",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes)
    {
        DeleteDeck(currentrow);
        this->selfsetup();
        ui->renamedeck->setDisabled(true);
        ui->editdeck->setDisabled(true);
        ui->deletebtn->setDisabled(true);
    }
}
//重命名条目
void deck_and_heros::renamedeck()
{
    int currentrow;
    currentrow=ui->deckinf->currentRow()+1;//获取当前行下标
    bool ok;
    QInputDialog *dialog1=new QInputDialog;
    QString titleprompt;
    //todo:限制输入字数,输入到一定字数截断 自行设计?
    titleprompt = dialog1->getText(this,"请设置卡组名","输入卡组名(不超过24个字符)",QLineEdit::Normal,ReadDeck(currentrow).Name,&ok).left(24);
    if(ok&&!titleprompt.isEmpty())
    {
        RenameDeck(titleprompt,currentrow);
        this->selfsetup();
        ui->renamedeck->setDisabled(true);
        ui->editdeck->setDisabled(true);
        ui->deletebtn->setDisabled(true);
    }
    delete dialog1;
    dialog1=nullptr;
}
//创立新卡组 跳转
void deck_and_heros::newdecksetup()
{
    ui->deletebtn->setDisabled(true);
    ui->editdeck->setDisabled(true);
    ui->renamedeck->setDisabled(true);
    int currentid;
    currentid=GetDeckNum()+1;
    choosecard=new choose;
    choosecard->setGeometry(this->geometry());
    choosecard->show();
    choosecard->choosesetup(chosen,false,currentid);
    connect(choosecard,&choose::chooseSceneBack,this,&deck_and_heros::choosecarddelete);
    this->close();
}
//编辑原有卡组 跳转
void deck_and_heros::choosecardsetup()
{
    ui->deletebtn->setDisabled(true);
    ui->editdeck->setDisabled(true);
    ui->renamedeck->setDisabled(true);
    int currentrow;
    currentrow=ui->deckinf->currentRow()+1;//获取当前行下标
    choosecard=new choose;
    choosecard->setGeometry(this->geometry());
    choosecard->show();
    choosecard->choosesetup(0,true,currentrow);
    connect(choosecard,&choose::chooseSceneBack,this,&deck_and_heros::choosecarddelete);
    this->close();
}
//编辑/创建卡组页面的释放
void deck_and_heros::choosecarddelete()
{
    this->setGeometry(choosecard->geometry());
    delete choosecard;
    choosecard=nullptr;
    this->selfsetup();
    this->show();
}

deck_and_heros::~deck_and_heros()
{
    delete ui;
}
