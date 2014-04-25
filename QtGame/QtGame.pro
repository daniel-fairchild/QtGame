#-------------------------------------------------
#
# Project created by QtCreator 2014-04-19T18:08:19
#
#-------------------------------------------------

QT       -= gui

LIBS += -L../QtGamepad -lQtGamepad
LIBS += -L../QtGCanvas -lQtGCanvas
# add more as they are written

TARGET = ../QtGame
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    qtgame.cpp

HEADERS += \
    ../qtgame.h \
    ../qtgfxsource.h

