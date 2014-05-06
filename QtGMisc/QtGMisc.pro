#-------------------------------------------------
#
# Project created by QtCreator 2014-04-28T15:24:26
#
#-------------------------------------------------

QT       -= core gui

TARGET = QtGMisc
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    debug.c

HEADERS +=\
    debug.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
