#ifndef QTGCANVAS_H
#define QTGCANVAS_H


#include <QtOpenGL/QGLWidget>
#include <QVector>
#include <QtOpenGL/QGLShaderProgram>
#include <QtOpenGL/QGLFunctions>

#include "drawqueue.h"
#include "../qtgfxsource.h"
#include "qtgshaderbundle.h"



class QtGCanvas : public QGLWidget, public QGLFunctions
{
    Q_OBJECT

public:

public:
    enum SHADERS {
        COUNT
    } ;

    QtGCanvas(size_t dritmsize, const QGLFormat& format, QWidget* parent = 0);
    bool set_shader(int shadename);
    QGLShaderProgram* get_shader();

//    virtual void set_gfx_src(QtGfxSource* src) = 0;


protected:
    void add_shader(int name_ref, const char* fragmentfn, const char* vertexfn, const char* geometryfn=NULL);
    QtGfxSource* gfx_src;

#define NUM_DQ 2
#define NUM_SHADERS 64
//    DrawQueue dqueues[NUM_DQ];
    ShaderBundle* shaders[NUM_SHADERS];

    int current_shader_name;
    int frameno;

private:

};

#endif // QTGCANVAS_H
