QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += network

CONFIG += c++11
# CONFIG += resources_big
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    card.cpp \
    choose.cpp \
    deck.cpp \
    deck_and_heros.cpp \
    fight.cpp \
    firstchoose.cpp \
    main.cpp \
    mainwindow.cpp \
    mylabel.cpp \
    playerchoose.cpp \
    retlabel.cpp \
    selectwidget.cpp \
    uistyle.cpp

HEADERS += \
    card.h \
    choose.h \
    deck.h \
    deck_and_heros.h \
    fight.h \
    firstchoose.h \
    mainwindow.h \
    mylabel.h \
    playerchoose.h \
    retlabel.h \
    selectwidget.h \
    uistyle.h

FORMS += \
    choose.ui \
    deck_and_heros.ui \
    fight.ui \
    firstchoose.ui \
    mainwindow.ui \
    playerchoose.ui \
    retlabel.ui \
    selectwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
