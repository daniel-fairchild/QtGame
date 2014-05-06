#ifndef QTGFXSOURCE_H
#define QTGFXSOURCE_H

#include "drawqueue.h"

//forward definition
class QtGCanvas;

class QtGfxSource
{
public:
    virtual void imprint_frame(QtgDrawQueue* queue) = 0;
    virtual bool init(QtGCanvas* canvas) = 0;
};

#endif // QTGFXSOURCE_H
