#ifndef DTEXTURE_H
#define DTEXTURE_H

#include <QtOpenGL/QGLFunctions>

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

    bool activate(bool intepolate);

    /**
     * @brief deactivate
     * @return
     */
    bool deactivate();

    /**
     * @brief texttureId
     * @return texture ID of the activated texture on the GPU
     */
    GLuint texttureId();


    /**
     * @brief imgData
     * @return a void pointer to a pnm_img_t*, defined in netphm.h
     */
    void *imgData();

    /**
     * @brief pnm_get_pixel
     * @param img
     * @param x
     * @param y
     * @return
     */
    void* getPixel(int x, int y);

    /**
     * @brief pnm_set_pixel
     * @param img
     * @param x
     * @param y
     * @param pixel
     */
    void setPixel(int x, int y, void* pixel);

    void setFormat(GLuint format);

    void store(const char* fname);

    int width();
    int height();

protected:
    GLuint _textureId;

    bool _activated;
    void* _img;

private:
};


#endif // DTEXTURE_H
