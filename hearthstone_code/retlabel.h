#ifndef RETLABEL_H
#define RETLABEL_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class retlabel;
}

class retlabel : public QWidget
{
    Q_OBJECT

public:
    explicit retlabel(QWidget *parent = nullptr);
    ~retlabel();
    void drawcardpic(int cardid);
    void selected(bool isselected);
    void SetBldAtk(int bld,int atk);
    void SetSleep(bool sleeping);

signals:
    void labelclicked();
    void showprompt();
    void hideprompt();
protected:
    virtual void mousePressEvent(QMouseEvent* ev);
    virtual void enterEvent(QEnterEvent *event);
    virtual void leaveEvent(QEvent *event);
private:
    Ui::retlabel *ui;
};

#endif // RETLABEL_H
