#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include <QtOpenGL/QGLFunctions>
#include "ortoprojector.h"


class RenderBuffer : public OrtoProjector
{
public:

    RenderBuffer(bool depth_texture);
    RenderBuffer(int aheight, int awidth, bool depth_texture);

    int pix_width();
    int pix_height();

    GLuint buffer_ref();
    GLuint texture_ref();
    GLuint depth_ref();

protected:
    int width;
    int height;

    void _initFBO(bool depth_texture);
    GLuint color_tex, fbo, depth_rb; // grid_tex, TODO
};




#endif // RENDERBUFFER_H
