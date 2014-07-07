#ifndef DTEXTURE_H
#define DTEXTURE_H

#include <QtOpenGL/QGLFunctions>
#include "pnm.h"


class DTexture
{
public:
    /**
     * @brief DTexture
     * @param height
     * @param width
     * @param format
     */
    DTexture(int width, int height, GLenum format);


    /**
     * @brief DTexture
     * @param filename
     */
    DTexture(const char* filename);

    ~DTexture();

    /**
     * @brief activate
     * @return
     */
    bool activate();

    /**
     * @brief deactivate
     * @return
     */
    bool deactivate();


    GLuint texttureId();

    pnm_img *imgData();

protected:
    GLuint _textureId;

    bool _activated;
    pnm_img * _img;

private:
    void _init();
};


#endif // DTEXTURE_H
