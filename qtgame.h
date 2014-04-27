#ifndef QTGAME_H
#define QTGAME_H

#include "QtGamepad/qtgamepad.h"
#include "QtGCanvas/qtgcanvas.h"
#include "QtGLink/qtglink.h"
#include "QtGMusic/qtgmusic.h"
#include "QtGSound/qtgsound.h"
#include "QtGStorage/qtgstorage.h"

#include "qtgfxsource.h"

class QtGame : public QtGfxSource
{
protected:
    QtGamepad* gamepad;
    QtGSound* sound;

    QApplication* app;
//    QtGCanvas* canvas;

public:
    QtGame();

//    virtual void init(QApplication* qapp, QtGCanvas* glcanv);

    virtual void quit() = 0;

};

#endif // QTGAME_H
