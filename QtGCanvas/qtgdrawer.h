#ifndef QTGDRAWER_H
#define QTGDRAWER_H

#include "draw_base_t.h"
#include "drawqueue.h"

#include <QGLFunctions>

#include <QVector2D>
#include <QVector3D>



typedef struct
{
    QVector3D position;
    QVector2D texCoord;
} VertexData;



class QtGDrawer
{
public:
    virtual void imprint(QtgDrawQueue* queue, void *source) = 0;
    virtual void draw(draw_base_t* imprinted) = 0;

};


#endif // QTGDRAWER_H
