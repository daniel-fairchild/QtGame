#ifndef QTGCANVAS_H
#define QTGCANVAS_H


#include <QtOpenGL/QGLWidget>
#include <QVector>
#include <QtOpenGL/QGLShaderProgram>

#include "drawqueue.h"
#include "../qtgfxsource.h"
#include "QtGCanvas/shaderbundle.h"

class QtGCanvas : public QGLWidget
{
    Q_OBJECT

public:

public:
    enum SHADERS {
        COUNT
    } ;

    QtGCanvas(size_t dritmsize, const QGLFormat& format, QWidget* parent = 0);
    void set_gfx_src(QtGfxSource* src);
    bool set_shader(QtGCanvas::SHADERS shadename);
    QGLShaderProgram* get_shader();


protected:
    void add_shader(QtGCanvas::SHADERS name, const char* fragmentfn, const char* vertexfn, const char* geometryfn=NULL);
    QtGfxSource* gfx_src;

    int window_width;
    int window_height;
    bool reload_shaders;


#define NUM_DQ 2
#define NUM_SHADERS 64
    DrawQueue dqueues[NUM_DQ];
    ShaderBundle* shaders[NUM_SHADERS];

    QtGCanvas::SHADERS current_shader_name;

private:

};

#endif // QTGCANVAS_H


/*

#include <QOpenGLTimeMonitor>

class TerrainScene : public QGLWidget
{
    Q_OBJECT

    QTimer *timer;

    float ax, ay, dist;
    float ang_x;
    float ang_y;
    int mouse_x0,mouse_y0;
    int window_width;
    int window_height;


    GLGraphics::ShaderProgramDraw shader;
    GLGraphics::ThreeDObject cow;
    GLuint m_vertexBuffer;

    QOpenGLTimeMonitor* m_timeMonitor;
    bool bench_frame = false;

public:
    TerrainScene( const QGLFormat& format, QWidget* parent = 0);

public slots:
//    void animate();

protected:
     void initializeGL();
     void resizeGL( int w, int h );
     void paintGL();
     void mousePressEvent(QMouseEvent *);
     void mouseReleaseEvent(QMouseEvent *);
     void mouseMoveEvent(QMouseEvent *);
     void keyPressEvent(QKeyEvent *);
     void keyReleaseEvent(QKeyEvent *);
};


*/
