#-------------------------------------------------
#
# Project created by QtCreator 2014-04-19T18:01:31
#
#-------------------------------------------------

QT       -= gui

TARGET = QtGamepad
TEMPLATE = lib

CONFIG += staticlib

#DEFINES += QTGAMEPAD_LIBRARY

SOURCES += qtgamepad.cpp \
    qtctrlcollection.cpp \
    SDL/gamepad.cpp \
    SDL/ctrlcollection.cpp

HEADERS += qtgamepad.h \ 
    qtctrlcollection.h \
    ctrl_types.h \
    SDL/gamepad.h \
    SDL/ctrlcollection.h

macx {
    INCLUDEPATH +=/opt/local/include/
#    LIBS += -L/opt/local/lib/ -lSDL.a
    LIBS += -l/opt/local/lib//libSDL.a
}

win32 {
    INCLUDEPATH +=$$PWD/../../SDL-1.2.15/include/
    LIBS += -L$$PWD/../../SDL-1.2.15/lib/ -lSDL
}
