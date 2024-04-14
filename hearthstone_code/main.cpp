#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>
#include "uistyle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(new NorwegianWoodStyle);
    QApplication::setPalette(QApplication::style()->standardPalette());
    MainWindow w;
    w.show();
    return a.exec();
}
