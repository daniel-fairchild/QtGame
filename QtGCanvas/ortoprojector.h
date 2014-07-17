#ifndef ORTOPROJECTOR_H
#define ORTOPROJECTOR_H

#include <QVector2D>


typedef struct {
    int pix_width;
    int pix_height;
    float coord_width;
    float coord_height;
} ortoPixProj_t;

class OrtoProjector
{
public:
    OrtoProjector();

    virtual int pix_height() = 0;
    virtual int pix_width() = 0;

    QVector2D ortoPixProj(ortoPixProj_t *proj);
};

#endif // ORTOPROJECTOR_H
