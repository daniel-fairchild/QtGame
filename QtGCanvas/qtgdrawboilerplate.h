#ifndef QTGDRAWBOILERPLATE_H
#define QTGDRAWBOILERPLATE_H

#include "qtgcanvas.h"
#include "qtgdrawer.h"
#include "dgl_vbo.h"

namespace drawers {

typedef struct {
    const char* aname;
    GLenum atype;
    GLint asize;
    size_t cstep;
    int a_loc;
} attrib_locdef_t;

class QtGDrawBoilerPlate : public QtGDrawer
{

public:
    QtGDrawBoilerPlate(QtGCanvas* pb_canvas, QtGShaderBundle* shader);

protected:
    virtual void _init_vbo_attribs() = 0;
    virtual void _init_vbo_data() = 0;
    virtual void _bind_vbo() = 0;

    GLuint vboIds[2];

    attrib_locdef_t* vbo_attribs;
    size_t num_vbo_attribs;
    size_t calculated_stride;
    size_t expected_stride;

    void _shared_enable_attrs();

    QtGShaderBundle* shader;

private:
    QtGCanvas* _bp_canvas;


    // QtGDrawer interface
public:
    bool init();
    void deactivate();
};

}

#endif // QTGDRAWBOILERPLATE_H
