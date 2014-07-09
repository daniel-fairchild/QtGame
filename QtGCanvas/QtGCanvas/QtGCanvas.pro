#-------------------------------------------------
#
# Project created by QtCreator 2014-04-19T15:53:30
#
#-------------------------------------------------

! include( ../common.pri ) {
    error( Could not find the common.pri file! )
}

#CONFIG += staticlib
CONFIG += dll

QT += opengl core
QT -= gui

SOURCES += \
    qtgcanvas.cpp \
    drawqueue.cpp \
    qtgshaderbundle.cpp \
    qtgqueueman.cpp \
    qtgdrawboilerplate.cpp \
    ../texture/dtexture.cpp \
    ../texture/pnm.c

HEADERS += \
    ../qtgcanvas.h \
    ../drawqueue.h \
    ../qtgdrawer.h \
    ../draw_base_t.h \
    ../qtgshaderbundle.h \
    ../qtgqueueman.h \
    ../qtgdrawboilerplate.h \
    ../texture/dtexture.h \
    ../texture/pnm.h



TARGET = ../QtGCanvas
