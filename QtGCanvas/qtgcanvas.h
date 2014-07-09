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

#include "gcanvas.h"


typedef struct {
    int pix_width;
    int pix_height;
    float coord_width;
    float coord_height;
} ortoPixProj_t;

class QtGCanvas : public GCanvas, public QGLWidget, public QGLFunctions
{

public:
    QtGCanvas(QtGfxSource* game, QGLFormat* format = 0, QWidget* parent = 0);
    int set_shader(QtGShaderBundle* shader, QtGDrawer* owner);

    QVector3D rotationAxis;
    QQuaternion rotation;


    QVector2D ortoPixProj(ortoPixProj_t* proj);

protected:
    QtGfxSource* gfx_src;

    GLuint active_shader;
    QtGDrawer* active_drawer;

    QtGQueueMan* queman;

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent *e);

    bool draggmode;
    QVector2D mousePressPosition;
    qreal angularSpeed;

protected:
    void paintGL();

    int last_resize_frame;
    QTimer timer;
};

#endif // QTGCANVAS_H
