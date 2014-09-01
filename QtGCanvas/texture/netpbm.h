#ifndef NETPBM_H
#define NETPBM_H


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>



typedef struct {
    unsigned char R;
    unsigned char G;
    unsigned char B;
} pnm_pixmap;

typedef struct {
    int width, height;
    int max_color;
    int p;
    void *pixels;
} pnm_img_t;

typedef enum {
    UNDEFINED_PIXMAP = 0,
    ASCII_BITMAP = 1,
    ASCII_GREYMAP = 2,
    ASCII_PIXMAP = 3,
    BINARY_BITMAP = 4,
    BINARY_GREYMAP = 5,
    BINARY_PIXMAP = 6
} pnm_image_type;

class NetPBM
{


public:
    static void* pnm_get_pixel(pnm_img_t* img, int x, int y);

    static void pnm_set_pixel(pnm_img_t *img, int x, int y, void* pixel);

    static pnm_img_t *pnm_create(int width, int height, int p);


    static pnm_img_t *pnm_read(const char file_name[]);

    static void pnm_write(pnm_img_t *img, const char file_name[]);


    static void pnm_destroy(pnm_img_t *img);

    static int pnm_set_imagetype(pnm_img_t* img, int p);
};

#endif // NETPBM_H
