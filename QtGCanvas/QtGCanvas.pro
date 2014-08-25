#TEMPLATE = subdirs
##SUBDIRS = \
##        OGLutils

## build must be last:
#CONFIG += ordered
#SUBDIRS += QtGCanvas

#-------------------------------------------------
#
# Project created by QtCreator 2014-04-19T15:53:30
#
#-------------------------------------------------

! include( ../common.pri ) {
    error( Could not find the common.pri file! )
}

QT += opengl core
QT -= gui

SOURCES += \
    qtgcanvas.cpp \
    drawqueue.cpp \
    qtgshaderbundle.cpp \
    qtgqueueman.cpp \
    qtgdrawboilerplate.cpp \
    texture/dtexture.cpp \
    renderbuffer.cpp \
    ortoprojector.cpp \
    dgl_vbo.cpp \
#    texture/pnm.c \

HEADERS += \
    qtgcanvas.h \
    drawqueue.h \
    qtgdrawer.h \
    draw_base_t.h \
    qtgshaderbundle.h \
    qtgqueueman.h \
    qtgdrawboilerplate.h \
    texture/dtexture.h \
    renderbuffer.h \
    ortoprojector.h \
    dgl_vbo.h \
#    texture/pnm.h \


TARGET = QtGCanvas
