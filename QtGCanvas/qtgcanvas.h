#ifndef QTGCANVAS_H
#define QTGCANVAS_H


#include <QtOpenGL/QGLWidget>
#include <QVector>
#include <QtOpenGL/QGLShaderProgram>
#include <QtOpenGL/QGLFunctions>

#include "drawqueue.h"
#include "qtgfxsource.h"
#include "qtgshaderbundle.h"
#include "qtgqueueman.h"



class QtGCanvas : public QGLWidget, public QGLFunctions
{

public:
    QtGCanvas(QtGfxSource* game, QGLFormat format, QWidget* parent = 0);
    void set_shader(QtGShaderBundle* shader);

//    virtual QMatrix4x4* MV_Projection() = 0;

protected:
    QtGfxSource* gfx_src;

    GLuint active_shader;

    QtGQueueMan* queman;
    QtGfxSource* game;

private:

};

#endif // QTGCANVAS_H
