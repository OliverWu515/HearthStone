#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <deck_and_heros.h>
#include <playerchoose.h>
#include <help.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    deck_and_heros *choosedeck= nullptr;
    playerchoose *playerchoosedeck=nullptr;
public slots:
    void deckscenesetup();
    void deckscenedelete();
    void playerchoosesetup();
    void playerchoosedelete();

private:
    Ui::MainWindow *ui;
    int validdecknum=0;
    void abletostartgame();
};
#endif // MAINWINDOW_H
