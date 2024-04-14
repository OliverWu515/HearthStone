#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>

class mylabel : public QLabel
{
    Q_OBJECT
public:
    explicit mylabel(QWidget *parent = nullptr);
    void drawheropic(int heroid);
    void drawskillpic(bool d,int heroid);
    void drawcardpic(int cardid);
    void drawgraypic(int cardid);
    void mousePressEvent(QMouseEvent* ev);
    void enterEvent(QEnterEvent *event);
    void leaveEvent(QEvent *event);
signals:
    void labelclicked();
    void labeldblclicked();
    void showprompt();
    void hideprompt();
};

#endif // MYLABEL_H
