#ifndef QTGDRAWBOILERPLATE_H
#define QTGDRAWBOILERPLATE_H

#include "qtgcanvas.h"
#include "qtgdrawer.h"

namespace drawers {

typedef struct {
    const char* aname;
    GLenum atype;
    GLint asize;
    size_t cstep;
    int a_loc;
} vbo_locdef_t;


class QtGDrawBoilerPlate : public QtGDrawer
{
public:
    QtGDrawBoilerPlate();


protected:
    void _enable_vbo();

    virtual void _vbo_attribs() = 0;
    virtual void _vbo_data() = 0;

    QtGCanvas* canvas;
    QtGShaderBundle* shader;
    GLuint vboIds[2];

    vbo_locdef_t* vbo_attribs;
    size_t num_vbo_attribs;
    size_t instance_stride;

    // QtGDrawer interface
public:
    bool init();
    void deactivate();
};

}

#endif // QTGDRAWBOILERPLATE_H
