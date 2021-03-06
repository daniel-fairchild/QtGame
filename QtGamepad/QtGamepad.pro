#-------------------------------------------------
#
# Project created by QtCreator 2014-04-19T18:01:31
#
#-------------------------------------------------

! include( ../common.pri ) {
    error( Could not find the common.pri file! )
}

QT       -= gui

TARGET = QtGamepad

#DEFINES += QTGAMEPAD_LIBRARY

SOURCES += qtgamepad.cpp \
    qtctrlcollection.cpp \
    SDL/gamepad.cpp \
    SDL/ctrlcollection.cpp

HEADERS += qtgamepad.h \ 
    qtctrlcollection.h \
    ctrl_types.h \
    SDL/gamepad.h \
    SDL/ctrlcollection.h \
\
    IOHIDLib/note.h \
\
    directInput/placeholder.h


macx {
    INCLUDEPATH +=/opt/local/include/
    LIBS += -L/opt/local/lib/ -lSDL
#    LIBS += -l/opt/local/lib/libSDL.a
}

win32 {
    INCLUDEPATH +=$$PWD/../../SDL-1.2.15/include
    LIBS += -L$$PWD/../../SDL-1.2.15/lib -lSDL
}
