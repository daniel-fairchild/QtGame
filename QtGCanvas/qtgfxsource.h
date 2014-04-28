#ifndef QTGFXSOURCE_H
#define QTGFXSOURCE_H

#include "drawqueue.h"

class QtGfxSource
{
public:
    virtual void next_frame(QtgDrawQueue* queue) = 0;
};

#endif // QTGFXSOURCE_H
