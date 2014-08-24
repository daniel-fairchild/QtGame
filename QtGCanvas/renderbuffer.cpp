#include <QApplication>
#include <QDesktopWidget>


#include "renderbuffer.h"
#include <qdebug.h>

static inline int _next2pow(int input){
    int out = 1;
    while (out < input)
        out= out<<1;
    return out;
}


RenderBuffer::RenderBuffer()
{
    int swidth = 0, sheight = 0;
    for (int i = 0; i < QApplication::desktop()->screenCount(); i++){
        QWidget* tscrn = QApplication::desktop()->screen(i);
        int twidth = tscrn->devicePixelRatio() * tscrn->width();
        int theight = tscrn->devicePixelRatio() * tscrn->height();
        swidth =  twidth > swidth? twidth:swidth;
        sheight = theight > sheight? theight:sheight;
    }

    this->height = _next2pow(sheight);
    this->width = _next2pow(swidth);

    _initFBO();
}

RenderBuffer::RenderBuffer(int aheight, int awidth)
{
    this->height = _next2pow(aheight);
    this->width = _next2pow(awidth);

    _initFBO();
}

int RenderBuffer::pix_width()
{
    return this->width;
}

int RenderBuffer::pix_height()
{
    return this->height;
}

GLuint RenderBuffer::buffer_ref()
{
    return this->fbo;
}

GLuint RenderBuffer::texture_ref()
{
    return this->color_tex;
}

GLuint RenderBuffer::depth_ref()
{
    return this->depth_rb;
}

void RenderBuffer::_initFBO()
{
    glGenFramebuffers(1, &fbo);
    glGenTextures(1, &color_tex);

//    glGenRenderbuffers(1, &depth_rb);
    glGenTextures(1, &depth_rb);

    glBindTexture(GL_TEXTURE_2D, color_tex);
    //NULL means reserve texture memory, but texels are undefined
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 this->pix_width(), this->pix_height(),
                 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

//    GLfloat maxAniso;
//    glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAniso);

//    glBindRenderbuffer(GL_RENDERBUFFER, depth_rb);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16,
//                          this->pix_width(), this->pix_height());

    glBindTexture(GL_TEXTURE_2D, depth_rb);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, this->pix_width(), pix_height(), 0,
                 GL_DEPTH_COMPONENT, GL_UNSIGNED_SHORT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // //-------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // specify texture as color attachment
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_tex, 0);
    // specify depth_rb as depth attachment
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_rb);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_rb, 0);

    // check for framebuffer complete
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(status != GL_FRAMEBUFFER_COMPLETE){
        qDebug() << "!GL_FRAMEBUFFER_COMPLETE:" <<status;
    }
}

