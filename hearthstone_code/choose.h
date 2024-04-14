#ifndef CHOOSE_H
#define CHOOSE_H

#include <QMainWindow>
#include "ui_selectwidget.h"
#include <selectwidget.h>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <card.h>
#include<deck.h>

namespace Ui {
class choose;
}

class choose : public QMainWindow
{
    Q_OBJECT

public:
    explicit choose(QWidget *parent = nullptr);
    ~choose();
    void choosesetup(int temp,bool hero_or_deck_id,int deck_id);
    void setuppages(int whichpage,bool page1_or_2);

signals:
    void chooseSceneBack();

private:
    CARD Card[MaxCard+1];
    Ui::choose *ui;
    //listwidget的项,0为起始
    QListWidgetItem *item1[MaxCard+1]={nullptr};
    QListWidgetItem *item2[MaxCard+1]={nullptr};
    //以按钮为索引,0为起始
    int usedtimes[MaxCard+1]={0};
    int usedtimes2[MaxCard+1]={0};
    //以卡片ID为索引,1为起始
    int cardusedtimes[MaxCard+1]={0};
    int positionset1[MaxCard+1]={0};
    int positionset2[MaxCard+1]={0};
    //以行为索引,1为起始
    int deckcard[31]={0};
    int rows=0;
    int cnt=0;
    int heroid=0;
    bool new_or_edit;
    int deckid;
    //获取某职业的卡牌数及编号
    int cardindex[MaxCard+1]={0};
    int cardindex2[MaxCard+1]={0};
    int totalnum1,totalpages1;
    int totalnum2,totalpages2;
    deck currentdeck;
    //两页的页面文件
    selectwidget *tab1pages[10];
    selectwidget *tab2pages[10];
};

#endif // CHOOSE_H
