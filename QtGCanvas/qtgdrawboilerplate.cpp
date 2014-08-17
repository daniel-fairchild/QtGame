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
        _bp_canvas->glVertexAttribPointer(tld->a_loc, tld->asize, tld->atype, GL_FALSE, this->calculated_stride, (const void *)offset);
        offset+= tld->cstep;
    }
}

bool QtGDrawBoilerPlate::init()
{
    this->_bp_canvas->set_shader(this->shader, this);
    QGLShaderProgram* shdp = this->shader->program();

    // this method should set expected strid to value different from 0
    this->expected_stride = 0;
    this->_init_vbo_attribs();
    if (!this->expected_stride){
        qDebug() << "expected stride not set!";
        return false;
    }

    this->_init_vbo_data();

    if (QtGCanvas::gl_error_test(__FILE__, __LINE__)){
        qDebug() << "Pre Boilerplate drawer init error: ";
        return false;
    }


    calculated_stride = 0;
    for(size_t i = 0; i < this->num_vbo_attribs; i++){
        (this->vbo_attribs+i)->a_loc = shdp->attributeLocation((this->vbo_attribs+i)->aname);
        calculated_stride+= (this->vbo_attribs+i)->cstep;
    }
    if (this->expected_stride != this->calculated_stride){
        qDebug() << "expected stride:" <<
                    this->expected_stride <<
                    " different from calculated stride: "<<
                    this->calculated_stride;
        return false;
    }


    if (QtGCanvas::gl_error_test(__FILE__, __LINE__)){
        qDebug() << "Boilerplate drawer init error: ";
        return false;
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
