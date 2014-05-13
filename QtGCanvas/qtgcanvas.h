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
    int set_shader(QtGShaderBundle* shader, QtGDrawer* owner);


//    virtual QMatrix4x4* MV_Projection() = 0;
    QQuaternion rotation;

protected:
    QtGfxSource* gfx_src;

    GLuint active_shader;
    QtGDrawer* active_drawer;

    QtGQueueMan* queman;
    QtGfxSource* game;


    QVector3D rotationAxis;


    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent *e);

    bool draggmode;
    QVector2D mousePressPosition;
    qreal angularSpeed;


private:




protected:



};

#endif // QTGCANVAS_H
