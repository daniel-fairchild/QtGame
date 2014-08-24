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
#include "ortoprojector.h"
#include "dgl_vbo.h"


class QtGCanvas : public GCanvas, public QGLWidget, public QGLFunctions, public  OrtoProjector
{

public:
    QtGCanvas(QtGfxSource* game, QGLFormat* format = 0, QWidget* parent = 0);
    ~QtGCanvas();

    int set_shader(QtGShaderBundle* shader, QtGDrawer* owner);

    QVector3D rotationAxis;
    QQuaternion rotation;

    int pix_width();
    int pix_height();

    static bool gl_error_test(const char *fname, int line);


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

    void paintGL();
    void resizeGL(int w, int h);

    int last_resize_frame;
    QTimer timer;
};

#endif // QTGCANVAS_H
