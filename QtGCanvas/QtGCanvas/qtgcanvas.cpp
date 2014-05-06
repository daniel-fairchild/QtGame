#include "../qtgcanvas.h"

//#include "../OGLutils/GLGraphics/Core3_2_context.h"
//#include "../OGLutils/GLGraphics/GLHeader.h"

#include <QDebug>
#include <QFile>

//QtGCanvas::QtGCanvas(size_t dritmsize, const QGLFormat& format, QWidget* parent)
//    : QGLWidget(format, parent)
//{
////    this->shaders = new QVector<ShaderBundle*>(10);
////    for (int i = 0; i < NUM_DQ; i++)
////        this->dqueues[i].set_draw_item_size(dritmsize);

//    this->frameno = 0;
//    this->current_shader_name = -1;
//}

/*
bool QtGCanvas::set_shader(int shdnme){
    if (this->current_shader_name != shdnme){
        this->current_shader_name = shdnme ;
        this->shaders[shdnme]->prog()->bind();
        return true;
    }
    return false;
}

void QtGCanvas::add_shader(int name_ref, const char* fragment, const char*  vertex, const char* geometry){
    ShaderBundle* sb = new ShaderBundle(this->context(), fragment, vertex, geometry);
    this->shaders[name_ref] = sb;
}


QGLShaderProgram* QtGCanvas::QtGCanvas::get_shader(){
    return this->shaders[this->current_shader_name]->prog();
}
*/



QtGCanvas::QtGCanvas(QtGfxSource *agame, QGLFormat format, QWidget *parent) : QGLWidget(format, parent)
{
    this->game = agame;
}
