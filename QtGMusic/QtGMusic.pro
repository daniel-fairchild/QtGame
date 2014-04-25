#-------------------------------------------------
#
# Project created by QtCreator 2014-04-19T18:00:20
#
#-------------------------------------------------

QT       += multimedia

QT       -= gui
CONFIG += staticlib

TARGET = QtGMusic
TEMPLATE = lib

DEFINES += QTGMUSIC_LIBRARY

SOURCES += qtgmusic.cpp

HEADERS += qtgmusic.h\
        qtgmusic_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
