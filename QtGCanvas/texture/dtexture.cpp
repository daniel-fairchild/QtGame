#include "dtexture.h"
#include <qdebug.h>

inline static GLuint _PNM2GL(int p){
    switch (p){
    case 1:
    case 4:
        printf("Bitmaps not supported!\n");
        return -1;
    case 2:
    case 5:
        return GL_ALPHA;
    case 3:
    case 6:
        return GL_RGB;
    default:
        printf("Unrecognized PPM format:p%d\n",p);
        return -1;
    }
}


inline static pnm_image_type _GL2PNM(GLuint f){
    switch (f){
    case GL_ALPHA:
    case GL_LUMINANCE:
        return BINARY_GREYMAP;
    case GL_RGB:
        return BINARY_PIXMAP;
    default:
        printf("Unrecognized GL format:p%d\n",f);
        return UNDEFINED_PIXMAP;
    }
}

bool DTexture::activate()
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _img->width, _img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, _img->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLenum err = glGetError();
    if (err != GL_NO_ERROR){
        qDebug() << "texture init error: ";
        return false;
    }
    return true;
}

bool DTexture::deactivate()
{
    if (!this->_activated)
        return false;
    else {
        glDeleteTextures(1, &this->_textureId);
        return true;
    }
}

GLuint DTexture::texttureId()
{
    return this->_textureId;
}

pnm_img *DTexture::imgData()
{
    return this->_img;
}

void DTexture::_init()
{

}


DTexture::DTexture(int width, int height, GLenum format)
{
    this->_img = pnm_create(width, height, _GL2PNM(format));
}


DTexture::DTexture(const char *filename)
{
    this->_img = pnm_read(filename);
}

DTexture::~DTexture()
{
    this->deactivate();
    pnm_destroy(this->_img);
}
