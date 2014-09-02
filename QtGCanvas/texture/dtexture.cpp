#include "dtexture.h"
#include <qdebug.h>
#include "netpbm.h"

#include <QtCore/QFile>

inline static GLuint _PNM2GL(int p){
    switch (p){
    case 1:
    case 4:
        printf("Bitmaps not supported!\n");
        return -1;
    case 2:
    case 5:
        return GL_LUMINANCE;
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
    return this->activate(false);
}

bool DTexture::activate(bool intepolate)
{
    pnm_img_t* t_img = (pnm_img_t*)this->_img;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, _PNM2GL(t_img->p), t_img->width, t_img->height, 0, _PNM2GL(t_img->p), GL_UNSIGNED_BYTE, t_img->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, intepolate ? GL_LINEAR : GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, intepolate ? GL_LINEAR : GL_NEAREST);

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

void *DTexture::imgData()
{
    return this->_img;
}

void *DTexture::getPixel(int x, int y)
{
    return NetPBM::pnm_get_pixel(((pnm_img_t*)_img), x, y);
}

void DTexture::setPixel(int x, int y, void *pixel)
{
    NetPBM::pnm_set_pixel(((pnm_img_t*)_img), x, y, pixel);
}

void DTexture::setFormat(GLuint format)
{
    NetPBM::pnm_set_imagetype(((pnm_img_t*)_img), _GL2PNM(format));
}

void DTexture::store(const char *fname)
{
    NetPBM::pnm_write((pnm_img_t*)_img, fname);
}

int DTexture::width()
{
    return ((pnm_img_t*)_img)->width;
}

int DTexture::height()
{
    return ((pnm_img_t*)_img)->height;
}

DTexture::DTexture(int width, int height, GLenum format)
{
    this->_img = NetPBM::pnm_create(width, height, _GL2PNM(format));
}


DTexture::DTexture(const char *filename)
{
    this->_img = NetPBM::pnm_read(filename);
}

DTexture::~DTexture()
{
    this->deactivate();
    NetPBM::pnm_destroy((pnm_img_t*)this->_img);
}
