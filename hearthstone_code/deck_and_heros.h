#ifndef DECK_AND_HEROS_H
#define DECK_AND_HEROS_H

#include <QWidget>
#include <selectwidget.h>
#include <choose.h>

namespace Ui {
class deck_and_heros;
}

class deck_and_heros : public QWidget
{
    Q_OBJECT

public:
    explicit deck_and_heros(QWidget *parent = nullptr);
    ~deck_and_heros();
    choose *choosecard = nullptr;

signals:
    void chooseSceneBack();

public slots:
    void choosecardsetup();
    void choosecarddelete();
    void itemdeleted();
    void renamedeck();
private:
    QListWidgetItem *item[100]={nullptr};//listwidget的项
    int chosen=0;
    Ui::deck_and_heros *ui;
    int items=0;
    void newdecksetup();
    void selfsetup();
signals:

};

#endif // DECK_AND_HEROS_H
