#ifndef PLAYERCHOOSE_H
#define PLAYERCHOOSE_H

#include <QWidget>
#include <QListWidgetItem>
#include <QTcpSocket>
#include <fight.h>
#include <deck.h>

namespace Ui {
class playerchoose;
}

class playerchoose : public QWidget
{
    Q_OBJECT

public:
    explicit playerchoose(QWidget *parent = nullptr);
    ~playerchoose();
    fight *fightscene = nullptr;
public slots:
    void fightscenesetup();
    void fightscenedelete();
signals:
    void chooseSceneBack();

private slots:
    void on_connectbtn_clicked();

    void on_startgame_clicked();

private:
    void selfsetup();
    void slotGetServerData();
    Ui::playerchoose *ui;
    int items=0;
    int deckid[100]={0};
    QListWidgetItem *item[100]={nullptr};//listwidget的项
    bool player1chosen=false;
    bool buttonstatus=true;//开始按钮的功能
    int myid;//自己编号
    int rivalid;//对手编号
    int _intOfRivalSocket;  //这个是对手的套接字，对战时要把它发给服务器，然后服务器用它联系对手
    QTcpSocket* _socket = nullptr;
    bool starting=false;//是否可以开始
    deck newdeck;
};

#endif // PLAYERCHOOSE_H
