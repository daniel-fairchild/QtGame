#ifndef DGL_VBO_H
#define DGL_VBO_H


#include <QtOpenGL/QGLFunctions>

typedef struct {
    void* attr_data;
    GLushort* indx_data;
    void* indx_offset;
    GLushort indx_data_skip;
} vbo_ref_t;

typedef struct {
//    void* data;
//    GLuint* indexes;

    size_t num_verts;
    size_t num_indexes;
    size_t data_stride;
} vbo_def_t;

class DGL_VBO
{
public:
    DGL_VBO();

    DGL_VBO(size_t indx_size, size_t atrr_size);
    ~DGL_VBO();

    vbo_ref_t reserve(vbo_def_t* vref);

    bool flush2gpu();
    void bind();

    void _shared_init(size_t atrr_size, size_t indx_size);
private:
    GLuint _vboIds[2];
    unsigned char* _attr_buf;
    size_t _used_attr;

    GLushort* _indx_buf;
    size_t _used_indx;

    size_t req_indx;
    size_t req_attr;
};

#endif // DGL_VBO_H
