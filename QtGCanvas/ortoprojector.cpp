#include "ortoprojector.h"

OrtoProjector::OrtoProjector()
{
}


static inline float _suborto(float world, int scrnpix, int mdlpix){
    return 2.0* mdlpix / (world * scrnpix);
}

QVector2D OrtoProjector::ortoPixProj(ortoPixProj_t *proj)
{
    return QVector2D (
                _suborto(proj->coord_width, this->pix_width(), proj->pix_width),
                _suborto(proj->coord_height, this->pix_height(), proj->pix_height));
}
