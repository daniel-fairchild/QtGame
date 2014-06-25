#include "../qtgdrawboilerplate.h"

drawers::QtGDrawBoilerPlate::QtGDrawBoilerPlate(){}

void drawers::QtGDrawBoilerPlate::_enable_vbo()
{
    canvas->glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    canvas->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);

    quintptr offset = 0;

    for (int i = 0; i < num_vbo_attribs; i++){
        vbo_locdef_t* tld = vbo_attribs+i;
        canvas->glEnableVertexAttribArray(tld->a_loc);
        canvas->glVertexAttribPointer(tld->a_loc, tld->asize, tld->atype, GL_FALSE, this->instance_stride, (const void *)offset);
        offset+= tld->cstep;
    }
}


bool drawers::QtGDrawBoilerPlate::init()
{
    this->shader->compile(this->canvas->context());
    this->canvas->set_shader(this->shader, this);

    QGLShaderProgram* shdp = this->shader->program();
    canvas->glGenBuffers(2, vboIds);

    this->_vbo_attribs();

    instance_stride = 0;
    for(int i = 0; i < this->num_vbo_attribs; i++){
        (this->vbo_attribs+i)->a_loc = shdp->attributeLocation((this->vbo_attribs+i)->aname);
        instance_stride+= (this->vbo_attribs+i)->cstep;
    }
    _enable_vbo();

    _vbo_data();

    GLenum err = glGetError();
    if (err != GL_NO_ERROR){
        qDebug() << "Boilerplate drawer init error!";
        return false;
    }
    return true;
}

void drawers::QtGDrawBoilerPlate::deactivate()
{
    canvas->glBindBuffer(GL_ARRAY_BUFFER, 0);
    canvas->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    for(int i =0; i < this->num_vbo_attribs; i++){
        canvas->glDisableVertexAttribArray((vbo_attribs+i)->a_loc);
    }
    shader->program()->release();
}
