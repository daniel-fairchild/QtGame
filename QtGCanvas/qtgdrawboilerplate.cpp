#include "qtgdrawboilerplate.h"

namespace drawers {

QtGDrawBoilerPlate::QtGDrawBoilerPlate(QtGCanvas *pb_canvas, QtGShaderBundle *shader){
    this->_bp_canvas = pb_canvas;
    this->shader = shader;
}

void QtGDrawBoilerPlate::_shared_enable_attrs()
{
    quintptr offset = 0;

    for (size_t i = 0; i < num_vbo_attribs; i++){
        vbo_locdef_t* tld = vbo_attribs+i;
        _bp_canvas->glEnableVertexAttribArray(tld->a_loc);
        _bp_canvas->glVertexAttribPointer(tld->a_loc, tld->asize, tld->atype, GL_FALSE, this->instance_stride, (const void *)offset);
        offset+= tld->cstep;
    }
}

bool QtGDrawBoilerPlate::init()
{
    this->_bp_canvas->set_shader(this->shader, this);
    QGLShaderProgram* shdp = this->shader->program();

    this->_init_vbo_attribs();
    this->_init_vbo_data();

    instance_stride = 0;
    for(size_t i = 0; i < this->num_vbo_attribs; i++){
        (this->vbo_attribs+i)->a_loc = shdp->attributeLocation((this->vbo_attribs+i)->aname);
        instance_stride+= (this->vbo_attribs+i)->cstep;
    }    
    QtGCanvas::gl_error_test(__FILE__, __LINE__);

    for (int i = 0; i < this->num_vbo_attribs; i ++){
        qDebug() << this->vbo_attribs[i].aname << ": " << this->vbo_attribs[i].a_loc;
    }
    return true;
}

void QtGDrawBoilerPlate::deactivate()
{
    for(size_t i =0; i < this->num_vbo_attribs; i++){
        _bp_canvas->glDisableVertexAttribArray((vbo_attribs+i)->a_loc);
    }
    shader->program()->release();
}
}
