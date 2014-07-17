#ifndef DGL_VBO_H
#define DGL_VBO_H


#include <QtOpenGL/QGLFunctions>

class DGL_VBO
{
public:
    DGL_VBO();

    int append(void* data, size_t num_data, GLuint* indexes, size_t num_indexes, size_t data_stride);

    void switch_part(int partref);

    bool actualize();

    bool deallocate();


private:
    unsigned char* _buffer;
    size_t _num_parts;
};

#endif // DGL_VBO_H
