#-------------------------------------------------
#
# Project created by QtCreator 2014-04-19T17:54:12
#
#-------------------------------------------------

QT       -= gui
QT += multimedia

TARGET = QtGSound
TEMPLATE = lib
CONFIG += staticlib

SOURCES += qtgsound.cpp

HEADERS += qtgsound.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
