#include "choose.h"
#include "ui_choose.h"
#include <QDebug>
#include <QStackedWidget>
#include <QToolButton>
#include <QCheckBox>
#include <QTimer>
#include <QString>
#include <QTabWidget>
#include <QMessageBox>
#include <mylabel.h>
#include <QInputDialog>
#include <string.h>

choose::choose(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::choose)
{
    ui->setupUi(this);
    showFullScreen();
    setWindowTitle("套牌选择页面");
    setWindowIcon(QIcon(":/1/pic/logo_1.jpg"));
    //返回/保存按钮设置
    connect(ui->returntolast,&QPushButton::clicked,[=](){
        currentdeck.Hero=this->heroid;
        currentdeck.Name=ui->promptcard->text();
        int sumcard=1;
        for(int i=1;i<=rows;i++)
        {
            if(cardusedtimes[deckcard[i]]==1)
            {
                currentdeck.CardID[sumcard]=deckcard[i];
                sumcard++;
            }
            else if(cardusedtimes[deckcard[i]]==2)
            {
                currentdeck.CardID[sumcard]=deckcard[i];
                sumcard++;
                currentdeck.CardID[sumcard]=deckcard[i];
                sumcard++;
            }
        }
        currentdeck.Sum=sumcard-1;
        SaveDeck(this->deckid,currentdeck);
        int totalnum=GetDeckNum()+1;
        if(this->new_or_edit==false) SetDeckNum(totalnum);
        //发出返回信号 选卡组界面监听信号
        emit chooseSceneBack();
    });
    //写入全部卡牌信息(不包括图片)
    SetCard(Card);
    //提示数量信息设置
    ui->label->setText("已选卡牌数："+QString::number(cnt));
    //删除按钮设置
    ui->deletebutton->setText("删除该卡牌");
    if(ui->cardsinf->currentRow()==-1)ui->deletebutton->setDisabled(true);//初始删除按钮不可用
    //一旦有卡被选中则启用删除按钮
    connect(ui->cardsinf,&QListWidget::itemClicked,[=](){
        ui->deletebutton->setEnabled(true);
    });
    ui->herotab->setFixedWidth(this->width()*0.7);
    ui->herotab->setFixedHeight(this->height()*0.97);
    //卡组名提示框设计
    ui->promptcard->setFont(QFont("华文楷体",14));
    connect(ui->promptcard,&mylabel::labelclicked,[=](){
        bool ok;
        QInputDialog *dialog1=new QInputDialog;
        QString titleprompt;
        //todo:限制输入字数,输入到一定字数截断
        titleprompt = dialog1->getText(this,"请设置卡组名","输入卡组名(不超过24个字符)",QLineEdit::Normal,ui->promptcard->text(),&ok).left(24);
        if(ok&&!titleprompt.isEmpty())  ui->promptcard->setText(titleprompt);
        delete dialog1;
        dialog1=nullptr;
    });
    //翻页按钮样式设置
    ui->lastpage->setStyleSheet("background:rgba(0,0,0,0)");
    ui->nextpage->setStyleSheet("background:rgba(0,0,0,0)");
    ui->lastpage->setIcon(QIcon(":/1/pic/leftarrow.png"));
    ui->nextpage->setIcon(QIcon(":/1/pic/rightarrow.png"));
    ui->lastpage_2->setStyleSheet("background:rgba(0,0,0,0)");
    ui->nextpage_2->setStyleSheet("background:rgba(0,0,0,0)");
    ui->lastpage_2->setIcon(QIcon(":/1/pic/leftarrow.png"));
    ui->nextpage_2->setIcon(QIcon(":/1/pic/rightarrow.png"));
}

void choose::choosesetup(int temp,bool hero_or_deck_id,int deck_id)
{
    this->new_or_edit=hero_or_deck_id;
    this->deckid=deck_id;
    //新创
    if(hero_or_deck_id==false) this->heroid=temp;
    //编辑已有
    else{
        currentdeck=ReadDeck(deck_id);
        this->heroid=currentdeck.Hero;
    }
    //设置初始页面及页签名称
    ui->herotab->setCurrentIndex(0);
    ui->herotab->setTabText(0,GetHeroName(heroid));
    ui->herotab->setTabText(1,"中立/通用");
    //总卡牌数及页面数
    totalnum1=GetHeroCard(heroid,cardindex,Card);
    totalnum2=GetHeroCard(0,cardindex2,Card);
    totalpages1=totalnum1/6;
    totalpages2=totalnum2/6;
    qDebug()<<QString::number(totalnum1)<<"  "<<QString::number(totalpages1);
    qDebug()<<QString::number(totalnum2)<<"  "<<QString::number(totalpages2);
    if(totalnum1!=0)
    {
        for (int i=0;i<=totalpages1;i++)
        {
            tab1pages[i] = new selectwidget;
            ui->stackedWidget->addWidget(tab1pages[i]);
        }
        this->setuppages(0,false);
    }
    if(totalnum2!=0)
    {
        for (int i=0;i<=totalpages2;i++)
        {
            tab2pages[i] = new selectwidget;
            ui->stackedWidget_2->addWidget(tab2pages[i]);
        }
        this->setuppages(0,true);
    }
    if(totalnum1!=0)
    {
        for(int i=0;i<=totalpages1;i++)
        {
            int maxcardnum;
            if(i<totalpages1) maxcardnum=6;
            else if (i==totalpages1) maxcardnum=totalnum1%6;
            for(int j=0;j<maxcardnum;j++)
            {
                //定义条目,每个按钮一条
                item1[6*i+j]=new QListWidgetItem;
                item1[6*i+j]->setSizeHint(QSize(10,40));
                item1[6*i+j]->setFont(QFont("华文楷体",12));
                connect(tab1pages[i]->buttonlist[j],&QToolButton::clicked,[=](){
                    if(cnt==30) QMessageBox::information(this,"提示","卡牌数目已达上限！");
                    else{
                        if (usedtimes[6*i+j]==0)
                        {
                            //插入条目、设置大小
                            item1[6*i+j]->setText(QString::number(Card[cardindex[6*i+j+1]].Cost)+"   "+Card[cardindex[6*i+j+1]].Name);
                            int k;
                            for (k=1;k<=rows;k++)
                                if (Card[deckcard[k]].Cost>Card[cardindex[6*i+j+1]].Cost||(Card[deckcard[k]].Cost==Card[cardindex[6*i+j+1]].Cost&&deckcard[k]>cardindex[6*i+j+1]))
                                    break;
                            for (int m=rows;m>=k;m--)
                                deckcard[m+1]=deckcard[m];
                            deckcard[k]=cardindex[6*i+j+1];
                            for (int m=0;m<totalnum2;m++)
                                if (positionset2[m]>=k)
                                    positionset2[m]++;
                            for (int m=0;m<totalnum1;m++)
                                if (positionset1[m]>=k)
                                    positionset1[m]++;
                            ui->cardsinf->insertItem(k-1,item1[6*i+j]);//加入item
                            rows++;
                            positionset1[6*i+j]=k;
                            usedtimes[6*i+j]++;
                            cardusedtimes[cardindex[6*i+j+1]]++;
                            if(Card[cardindex[6*i+j+1]].Rarity) tab1pages[i]->buttonlist[j]->setDisabled(true);
                            cnt++;
                        }
                        else if(usedtimes[6*i+j]==1)
                        {
                            item1[6*i+j]->setText(QString::number(Card[cardindex[6*i+j+1]].Cost)+"   "+Card[cardindex[6*i+j+1]].Name+" （2）");
                            tab1pages[i]->buttonlist[j]->setDisabled(true);
                            usedtimes[6*i+j]++;
                            cardusedtimes[cardindex[6*i+j+1]]++;
                            cnt++;
                        }
                        //提示数量信息更新
                        ui->label->setText("已选卡牌数："+QString::number(cnt));
                    }
                });
            }
        }
    }
    if(totalnum2!=0)
    {
        for(int i=0;i<=totalpages2;i++)
        {
            int maxcardnum;
            if(i<totalpages2) maxcardnum=6;
            else if (i==totalpages2) maxcardnum=totalnum2%6;
            for(int j=0;j<maxcardnum;j++)
            {
                //定义条目,每个按钮一条
                item2[6*i+j]=new QListWidgetItem;
                item2[6*i+j]->setSizeHint(QSize(10,40));
                item2[6*i+j]->setFont(QFont("华文楷体",12));
                connect(tab2pages[i]->buttonlist[j],&QToolButton::clicked,[=](){
                    if(cnt==30) QMessageBox::information(this,"提示","卡牌数目已达上限！");
                    else{
                        if (usedtimes2[6*i+j]==0)
                        {
                            //插入条目、设置大小
                            item2[6*i+j]->setText(QString::number(Card[cardindex2[6*i+j+1]].Cost)+"   "+Card[cardindex2[6*i+j+1]].Name);
                            int k;
                            for (k=1;k<=rows;k++)
                                if (Card[deckcard[k]].Cost>Card[cardindex2[6*i+j+1]].Cost||(Card[deckcard[k]].Cost==Card[cardindex2[6*i+j+1]].Cost&&deckcard[k]>cardindex2[6*i+j+1]))
                                    break;
                            for (int m=rows;m>=k;m--)
                                deckcard[m+1]=deckcard[m];
                            deckcard[k]=cardindex2[6*i+j+1];
                            for (int m=0;m<totalnum2;m++)
                                if (positionset2[m]>=k)
                                    positionset2[m]++;
                            for (int m=0;m<totalnum1;m++)
                                if (positionset1[m]>=k)
                                    positionset1[m]++;
                            ui->cardsinf->insertItem(k-1,item2[6*i+j]);
                            rows++;
                            positionset2[6*i+j]=k;
                            usedtimes2[6*i+j]++;
                            cardusedtimes[cardindex2[6*i+j+1]]++;
                            if(Card[cardindex2[6*i+j+1]].Rarity) tab2pages[i]->buttonlist[j]->setDisabled(true);
                            cnt++;
                        }
                        else if(usedtimes2[6*i+j]==1)
                        {
                            item2[6*i+j]->setText(QString::number(Card[cardindex2[6*i+j+1]].Cost)+"   "+Card[cardindex2[6*i+j+1]].Name+" （2）");
                            tab2pages[i]->buttonlist[j]->setDisabled(true);
                            usedtimes2[6*i+j]++;
                            cardusedtimes[cardindex2[6*i+j+1]]++;
                            cnt++;
                        }
                        //提示数量信息更新
                        ui->label->setText("已选卡牌数："+QString::number(cnt));
                    }
                });
            }
        }
    }
    //设置删除按钮
    connect(ui->deletebutton,&QPushButton::clicked,[=](){
        int currentrow,current=-1;
        bool page;
        currentrow=ui->cardsinf->currentRow();//获取当前行下标
        cnt--;
        //提示数量信息设置
        ui->label->setText("已选卡牌数："+QString::number(cnt));
        if(cnt==0) ui->deletebutton->setDisabled(true);
        //获取当前行对应的按钮
        for(int j=0;j<MaxCard;j++)
        {
            if (positionset1[j]-1==currentrow)
            {
                current=j;
                page=true;
                break;
            }
            if (positionset2[j]-1==currentrow)
            {
                current=j;
                page=false;
                break;
            }
        }
        qDebug()<<positionset1[0];
        qDebug()<<QString::number(current)<<"  "<<QString::number(currentrow);
        //如果在第1页
        if(page)
        {
            if (usedtimes[current]==1)
            {
                if(Card[cardindex[current+1]].Rarity) tab1pages[current/6]->buttonlist[current%6]->setEnabled(true);
                item1[current] = ui->cardsinf->takeItem(currentrow);
                usedtimes[current]--;
                cardusedtimes[cardindex[current+1]]--;
                for (int m=currentrow+1;m<rows;m++)
                    deckcard[m]=deckcard[m+1];
                rows--;
                for(int m=0;m<totalnum1;m++)
                {
                    if(positionset1[m]>currentrow+1)  positionset1[m]--;
                    if(m==current) positionset1[current]=0;
                }
                for(int m=0;m<totalnum2;m++)
                    if(positionset2[m]>currentrow+1)  positionset2[m]--;
            }
            else if(usedtimes[current]==2)
            {
                tab1pages[current/6]->buttonlist[current%6]->setEnabled(true);
                item1[current]->setText(QString::number(Card[cardindex[current+1]].Cost)+"   "+Card[cardindex[current+1]].Name);
                usedtimes[current]--;
                cardusedtimes[cardindex[current+1]]--;
            }
        }
        //如果在第2页
        else
        {
            if(usedtimes2[current]==1)
            {
                if(Card[cardindex2[current+1]].Rarity) tab2pages[current/6]->buttonlist[current%6]->setEnabled(true);
                item2[current] = ui->cardsinf->takeItem(currentrow);
                usedtimes2[current]--;
                cardusedtimes[cardindex2[current+1]]--;
                for (int m=currentrow+1;m<rows;m++)
                    deckcard[m]=deckcard[m+1];
                rows--;
                for(int m=0;m<totalnum1;m++)
                    if(positionset1[m]>currentrow+1)  positionset1[m]--;
                for(int m=0;m<totalnum2;m++)
                {
                    if(positionset2[m]>currentrow+1)  positionset2[m]--;
                    if(m==current) positionset2[current]=0;
                }
            }
            else if(usedtimes2[current]==2)
            {
                tab2pages[current/6]->buttonlist[current%6]->setEnabled(true);
                item2[current]->setText(QString::number(Card[cardindex2[current+1]].Cost)+"   "+Card[cardindex2[current+1]].Name);
                usedtimes2[current]--;
                cardusedtimes[cardindex2[current+1]]--;
            }
        }
    });
    //关联切换页面操作与图片读写释放,页码显示框变化
    //tab1(specified)
    if(totalpages1)
    {
        connect(ui->lastpage,&QPushButton::clicked,[=](){
            ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()-1);
            if(ui->stackedWidget->currentIndex()<totalpages1)
            {
                tab1pages[ui->stackedWidget->currentIndex()+1]->deleteicons();
                this->setuppages(ui->stackedWidget->currentIndex(),false);
            }
        });
        connect(ui->nextpage,&QPushButton::clicked,[=](){
            ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex()+1);
            if(ui->stackedWidget->currentIndex()>0)
            {
                tab1pages[ui->stackedWidget->currentIndex()-1]->deleteicons();
                this->setuppages(ui->stackedWidget->currentIndex(),false);
            }
        });
    }
    connect(ui->stackedWidget,&QStackedWidget::currentChanged,[=](){
        ui->pagenum->setText("第"+QString::number(ui->stackedWidget->currentIndex()+1)+"页，共"+
                             QString::number(ui->stackedWidget->count())+"页");
    });
    //tab2(neutral)
    connect(ui->lastpage_2,&QPushButton::clicked,[=](){
        ui->stackedWidget_2->setCurrentIndex(ui->stackedWidget_2->currentIndex()-1);
        if(ui->stackedWidget_2->currentIndex()<totalpages2)
        {
            tab2pages[ui->stackedWidget_2->currentIndex()+1]->deleteicons();
            this->setuppages(ui->stackedWidget_2->currentIndex(),true);
        }
    });
    connect(ui->nextpage_2,&QPushButton::clicked,[=](){
        ui->stackedWidget_2->setCurrentIndex(ui->stackedWidget_2->currentIndex()+1);
        if(ui->stackedWidget_2->currentIndex()>0)
        {
            tab2pages[ui->stackedWidget_2->currentIndex()-1]->deleteicons();
            this->setuppages(ui->stackedWidget_2->currentIndex(),true);
        }
    });
    connect(ui->stackedWidget_2,&QStackedWidget::currentChanged,[=](){
        ui->pagenum_2->setText("第"+QString::number(ui->stackedWidget_2->currentIndex()+1)+"页，共"+
                               QString::number(ui->stackedWidget_2->count())+"页");
    });
    //页码显示框初始化(未点击按钮时显示)
    ui->pagenum->setText("第"+QString::number(ui->stackedWidget->currentIndex()+1)+"页，共"+
                         QString::number(ui->stackedWidget->count())+"页");
    ui->pagenum_2->setText("第"+QString::number(ui->stackedWidget_2->currentIndex()+1)+"页，共"+
                           QString::number(ui->stackedWidget_2->count())+"页");

    if(hero_or_deck_id==true) {
        //模拟按钮点击以模拟卡被选的效果
        ui->promptcard->setText(currentdeck.Name);
        for(int m=1;m<=currentdeck.Sum;m++)
        {
            for(int i=1;i<=totalnum1;i++)
            {
                if(currentdeck.CardID[m]==cardindex[i])
                {
                    emit tab1pages[(i-1)/6]->buttonlist[(i-1)%6]->clicked();
                    break;
                }
            }
            for(int j=1;j<=totalnum2;j++)
            {
                if(currentdeck.CardID[m]==cardindex2[j])
                {
                    emit tab2pages[(j-1)/6]->buttonlist[(j-1)%6]->clicked();
                    break;
                }
            }
        }
    }
}
//翻到特定页面时画图
void choose::setuppages(int whichpage, bool page1_or_2)
{
    //如果在第1页
    if(page1_or_2==false)
    {
        if(whichpage<totalpages1) tab1pages[whichpage]->setcards(6,cardindex,1+6*whichpage);
        else if (whichpage==totalpages1)
        {
            tab1pages[whichpage]->setcards(totalnum1%6,cardindex,1+6*whichpage);
            tab1pages[whichpage]->lessbutton(totalnum1%6);
        }
    }
    //如果在第2页
    else
    {
        if(whichpage<totalpages2) tab2pages[whichpage]->setcards(6,cardindex2,1+6*whichpage);
        else if (whichpage==totalpages2)
        {
            tab2pages[whichpage]->setcards(totalnum2%6,cardindex2,1+6*whichpage);
            tab2pages[whichpage]->lessbutton(totalnum2%6);
        }
    }
}

choose::~choose()
{
    delete ui;
}
