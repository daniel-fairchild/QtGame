#-------------------------------------------------
#
# Project created by QtCreator 2014-04-19T18:05:46
#
#-------------------------------------------------

QT       += sql
QT       -= gui

TARGET = QtGStorage
TEMPLATE = lib
CONFIG += staticlib

SOURCES += qtgstorage.cpp

HEADERS += qtgstorage.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
