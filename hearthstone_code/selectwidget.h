#ifndef SELECTWIDGET_H
#define SELECTWIDGET_H

#include <QWidget>
#include <QToolButton>

namespace Ui {
class selectwidget;
}

class selectwidget : public QWidget
{
    Q_OBJECT

public:
    explicit selectwidget(QWidget *parent = nullptr);
    ~selectwidget();
    Ui::selectwidget *ui;
    //存放按钮地址
    QToolButton* buttonlist[6];

    //给每个按钮赋予意义
    void setcards(int cardnum,int cardindex[100],int startnum);
    //当按钮数量不能铺满全屏时特殊处理
    void lessbutton(int btnnum);
    void setdecks(int cardnum,int startnum);
    void deleteicons();
//private:
//    Ui::selectwidget *ui;
};

#endif // SELECTWIDGET_H
