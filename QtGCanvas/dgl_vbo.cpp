#include "dgl_vbo.h"


#define BUFSIZE (1<<20)*32

DGL_VBO::DGL_VBO()
{
    this->_buffer = (unsigned char*) calloc(1, BUFSIZE);
}
