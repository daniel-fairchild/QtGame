#-------------------------------------------------
#
# Project created by QtCreator 2014-04-19T18:01:31
#
#-------------------------------------------------

QT       -= core gui

TARGET = QtGamepad
TEMPLATE = lib

CONFIG += staticlib

#DEFINES += QTGAMEPAD_LIBRARY

SOURCES += qtgamepad.cpp

HEADERS += qtgamepad.h 

macx {
    LIBS += -L/opt/local/lib/
    INCLUDEPATH +=/opt/local/include/
    LIBS += -L../QtGame/QtGamepad -lQtGamepad
    LIBS += -L../QtGame/QtGCanvas -lQtGCanvas
    LIBS+= -lSDL
}
win32 {
    LIBS += -L$$PWD/../../SDL-1.2.15/lib/
    LIBS += -L..\QtGame\QtGCanvas\QtGCanvas -lQtGCanvas
    LIBS+= -lSDL
    INCLUDEPATH +=$$PWD/../../SDL-1.2.15/include/
}
