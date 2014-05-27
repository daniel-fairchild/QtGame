#ifndef QTGCANVAS_H
#define QTGCANVAS_H

//#include <QWindow>
#include <QtOpenGL/QGLWidget>
#include <QVector>
#include <QtOpenGL/QGLShaderProgram>
#include <QtOpenGL/QGLFunctions>
#include <QTimer>

#include "drawqueue.h"
#include "qtgfxsource.h"
#include "qtgshaderbundle.h"
#include "qtgqueueman.h"

class QtGCanvas : public QGLWidget, public QGLFunctions
{

public:
    QtGCanvas(QtGfxSource* game, QGLFormat format, QWidget* parent = 0);
    int set_shader(QtGShaderBundle* shader, QtGDrawer* owner);

    virtual void reset() = 0;



protected:
    virtual void gRender() = 0;
    virtual void _reset() = 0;


    QtGfxSource* gfx_src;

    GLuint active_shader;
    QtGDrawer* active_drawer;

    QtGQueueMan* queman;
    QtGfxSource* game;

    QQuaternion rotation;
    QVector3D rotationAxis;

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent *e);

    bool draggmode;
    QVector2D mousePressPosition;
    qreal angularSpeed;




protected:
    bool should_reset;
    bool should_exit;
    int last_resize_frame;

    void paintGL();

    QTimer timer;
};

#endif // QTGCANVAS_H
