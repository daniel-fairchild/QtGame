#include "dgl_vbo.h"


#define ATTRBUFFER (1<<20)*32
#define INDXBUFFER (1<<20)*4

DGL_VBO::DGL_VBO() : DGL_VBO::DGL_VBO(INDXBUFFER, ATTRBUFFER, 32)
{}

DGL_VBO::DGL_VBO(size_t indx_size, size_t atrr_size, size_t num_defs)
{
    unsigned char* tmp = (unsigned char*) calloc(1, indx_size+ atrr_size + num_defs*sizeof(vbo_ref_t));
    this->_ref_buf = (vbo_ref_t*)tmp;

    this->_indx_buf = tmp + sizeof(vbo_ref_t*num_defs);
    this->_attr_buf = this->_indx_buf + indx_size;

    this->_num_parts = 0;
    this->_attr_offset = 0;
    this->_indx_offset = 0;
}

size_t DGL_VBO::append(vbo_ref_t *vref)
{

}
