#-------------------------------------------------
#
# Project created by QtCreator 2014-04-19T18:04:25
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = QtGLink
TEMPLATE = lib
CONFIG += staticlib

SOURCES += qtglink.cpp

HEADERS += qtglink.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
