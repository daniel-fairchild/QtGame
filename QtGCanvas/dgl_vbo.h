#ifndef DGL_VBO_H
#define DGL_VBO_H


#include <QtOpenGL/QGLFunctions>

typedef struct {
    void* data;
    size_t num_data;
    GLuint* indexes;
    size_t num_indexes;
    size_t data_stride;
} vbo_ref_t;

class DGL_VBO
{
public:
    DGL_VBO();

    DGL_VBO(size_t indx_size, size_t atrr_size, size_t num_defs);

    size_t append(vbo_ref_t* vref);

    void switch_part(int partref);

    bool actualize();

    bool deallocate();

private:
    unsigned char* _attr_buf;
    unsigned char* _indx_buf;

    size_t _attr_offset;
    size_t _indx_offset;
    vbo_ref_t* _ref_buf;
    size_t _num_parts;
};

#endif // DGL_VBO_H
