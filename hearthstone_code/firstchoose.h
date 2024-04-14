#ifndef FIRSTCHOOSE_H
#define FIRSTCHOOSE_H

#include <QWidget>
#include <mylabel.h>
#include <card.h>
#include <deck.h>

namespace Ui {
class firstchoose;
}

class firstchoose : public QWidget
{
    Q_OBJECT

public:
    explicit firstchoose(QWidget *parent = nullptr);
    ~firstchoose();
    void fcsetup(int num,deck decktemp);
    int selected[4]={0};
signals:
    void chooseSceneBack(int c1,int c2,int c3,int c4);
private:
    Ui::firstchoose *ui;
    bool buttonstatus =false;
    bool changed[4]={false};
    int selected2[4]={0};
};

#endif // FIRSTCHOOSE_H
