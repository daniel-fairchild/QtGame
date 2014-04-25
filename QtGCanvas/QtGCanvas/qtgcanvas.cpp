#include "../qtgcanvas.h"

//#include "../OGLutils/GLGraphics/Core3_2_context.h"
//#include "../OGLutils/GLGraphics/GLHeader.h"

#include <QDebug>
#include <QFile>

QtGCanvas::QtGCanvas(size_t dritmsize, const QGLFormat& format, QWidget* parent)
    : QGLWidget(format, (QWidget*) parent)
{
//    this->shaders = new QVector<ShaderBundle*>(10);
    for (int i = 0; i < NUM_DQ; i++)
        this->dqueues[i].set_draw_item_size(dritmsize);
}

void QtGCanvas::set_gfx_src(QtGfxSource *src){
    this->gfx_src = src;
}


bool QtGCanvas::set_shader(QtGCanvas::SHADERS shdnme){
    if (this->current_shader_name != shdnme){
        this->current_shader_name = shdnme ;
        this->shaders[shdnme]->get_program()->bind();
        return true;
    }
    return false;
}

void QtGCanvas::add_shader(QtGCanvas::SHADERS name, const char* fragment, const char*  vertex, const char* geometry){
    ShaderBundle* sb = new ShaderBundle(this->context(), fragment, vertex, geometry);
    this->shaders[name] = sb;
}


QGLShaderProgram* QtGCanvas::QtGCanvas::get_shader(){
    return this->shaders[this->current_shader_name]->get_program();
}

