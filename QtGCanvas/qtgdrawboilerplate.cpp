#include "qtgdrawboilerplate.h"

namespace drawers {





//void QtGDrawBoilerPlate::_enable_vbo()
//{
//    canvas->glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
//    canvas->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);

//    _shared_enable_attrs();
//}

//void QtGDrawBoilerPlate::_enable_vbo(DGL_VBO *shared_vbo)
//{
//    shared_vbo->bind();
//    _shared_enable_attrs();
//}


static inline char* _gl_err2str(GLenum err){
    switch (err) {
    case GL_INVALID_ENUM:
        return "An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.";
        break;
    case GL_INVALID_VALUE:
        return "A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.";
        break;
    case GL_INVALID_OPERATION:
        return "The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.";
        break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return "The command is trying to render to or read from the framebuffer while the currently bound framebuffer is not framebuffer complete (i.e. the return value from glCheckFramebufferStatus is not GL_FRAMEBUFFER_COMPLETE). The offending command is ignored and has no other side effect than to set the error flag.";
        break;
    case GL_OUT_OF_MEMORY:
        return "There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.";
        break;
    default:
        return "Unknown GL error!";
        break;
    }
}

QtGDrawBoilerPlate::QtGDrawBoilerPlate(QtGCanvas *pb_canvas, QtGShaderBundle *shader){
    this->_bp_canvas = pb_canvas;
    this->shader = shader;
}

void QtGDrawBoilerPlate::_shared_enable_attrs()
{
    quintptr offset = 0;

    for (int i = 0; i < num_vbo_attribs; i++){
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
    for(int i = 0; i < this->num_vbo_attribs; i++){
        (this->vbo_attribs+i)->a_loc = shdp->attributeLocation((this->vbo_attribs+i)->aname);
        instance_stride+= (this->vbo_attribs+i)->cstep;
    }

    GLenum err = glGetError();
    if (err != GL_NO_ERROR){
        qDebug() << "Boilerplate drawer init error: " << _gl_err2str(err);
        return false;
    }
    return true;
}

void QtGDrawBoilerPlate::deactivate()
{
    //    canvas->glBindBuffer(GL_ARRAY_BUFFER, 0);
    //    canvas->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    for(int i =0; i < this->num_vbo_attribs; i++){
        _bp_canvas->glDisableVertexAttribArray((vbo_attribs+i)->a_loc);
    }
    shader->program()->release();
}
}
