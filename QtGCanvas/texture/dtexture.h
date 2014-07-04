#ifndef DTEXTURE_H
#define DTEXTURE_H

#include <QtOpenGL/QGLFunctions>


class DTexture
{
public:
    DTexture(int height, int width, GLenum format, void* data);
    bool activate();
    bool deactivate();

protected:
    GLuint textureId;
    void* data;

};




#endif // DTEXTURE_H
