#include "dgl_vbo.h"

#include <QDebug>
#include "../QtGCanvas/qtgcanvas.h"

#define INDXBUFFER (1<<16)*2 //maximum number of refereable indexes with glushort
#define ATTRBUFFER (1<<16)*128

void DGL_VBO::_shared_init(size_t atrr_size, size_t indx_size)
{
    this->req_attr = atrr_size;
    this->req_indx = indx_size;

    this->_indx_buf = (GLushort*) calloc(1, indx_size+ atrr_size);
    this->_attr_buf = (unsigned char*)((size_t)this->_indx_buf + indx_size);

    this->_used_attr = 0;
    this->_used_indx = 0;

    // gl initialization
    glGenBuffers(2, _vboIds);
    this->bind();
}

DGL_VBO::DGL_VBO()
{
    _shared_init(ATTRBUFFER, INDXBUFFER);
}


DGL_VBO::DGL_VBO(size_t indx_size, size_t atrr_size)
{   
    _shared_init(atrr_size, indx_size);
}

DGL_VBO::~DGL_VBO()
{
    glDeleteBuffers(2, this->_vboIds);
}

void DGL_VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, _vboIds[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vboIds[1]);
}

vbo_ref_t DGL_VBO::reserve(vbo_def_t *vref)
{
    vbo_ref_t outp;

    int modulo = this->_used_attr % vref->data_stride;

    // pad used buffer to nearest even higher multiplum
    this->_used_attr += modulo ? vref->data_stride - modulo: 0;

    size_t tatr  = ((size_t)this->_attr_buf + this->_used_attr);
    size_t tidx = ((size_t)this->_indx_buf + this->_used_indx);

    outp.attr_data = (void*)tatr;
    outp.indx_data = (GLushort*)tidx;

    size_t tdskip = this->_used_attr / vref->data_stride;
    if (tdskip > 1 <<16){
        qDebug() << "VBO index overflow detected!";
    }

    outp.indx_offset =  (void*)this->_used_indx;
    outp.indx_data_skip = (GLushort) (tdskip);

    this->_used_attr += vref->data_stride * vref->num_verts;
    this->_used_indx += vref->num_indexes * sizeof(GLushort);

    if (this->_used_attr > this->req_attr){
        qDebug() << "VBO attr buffer exceeds requested size!";
    }

    if (this->_used_indx > this->req_indx){
        qDebug() << "VBO index buffer exceeds requested size!";
    }

    return outp;
}

bool DGL_VBO::flush2gpu()
{
    this->bind();

    // Transfer vertex data to VBO 0
    glBufferData(GL_ARRAY_BUFFER, this->_used_attr, this->_attr_buf, GL_STATIC_DRAW);
    // Transfer index data to VBO 1
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->_used_indx, this->_indx_buf, GL_STATIC_DRAW);

    free(this->_indx_buf);

    this->_attr_buf = NULL;
    this->_indx_buf = NULL;

    return QtGCanvas::gl_error_test(__FILE__, __LINE__);
}
