#ifndef QTGFXSOURCE_H
#define QTGFXSOURCE_H

#include "QtGCanvas/drawqueue.h"

class QtGfxSource
{
public:
    virtual void next_frame(DrawQueue* queue) = 0;
};

#endif // QTGFXSOURCE_H
