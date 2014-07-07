#ifndef PPM_H
#define PPM_H

#define MAX_LINE_SIZE 1000

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _OPENM
#define PPM_PARALLEL_FOR #pragma omp parallel for 
#else
#define PPM_PARALLEL_FOR
#endif


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
} pnm_img;

typedef enum {
    UNDEFINED_PIXMAP = 0,
	ASCII_BITMAP = 1,
	ASCII_GREYMAP = 2,
	ASCII_PIXMAP = 3,
	BINARY_BITMAP = 4,
	BINARY_GREYMAP = 5,
    BINARY_PIXMAP = 6
} pnm_image_type;

typedef struct{
	void* cur_pix;
	void* first_pix;
	double pos_x;
	double pos_y;
	int pixwidth;
} cursor;

/**
 * @brief pnm_set_pixel
 * @param img
 * @param x
 * @param y
 * @param pixel
 */
void pnm_set_pixel(pnm_img *img, int x, int y, void* pixel);

/**
 * @brief pnm_get_pixel
 * @param img
 * @param x
 * @param y
 * @return
 */
void* pnm_get_pixel(pnm_img *img, int x, int y);

/**
 * @brief pnm_create
 * @param width
 * @param height
 * @param p
 * @return
 */
pnm_img *pnm_create(int width, int height, int p);

/**
 * @brief pnm_read
 * @param file_name
 * @return
 */
pnm_img *pnm_read(const char file_name[]);

/**
 * @brief pnm_write
 * @param img
 * @param file_name
 */
void pnm_write(pnm_img *img, const char file_name[]);

/**
 * @brief pnm_destroy
 * @param img
 */
void pnm_destroy(pnm_img *img);

/*
File Descriptor 	Type 					Encoding	Note
P1 					Portable bitmap 		ASCII		!Unsuported
P2 					Portable graymap 		ASCII
P3 					Portable pixmap 		ASCII
P4 					Portable bitmap 		Binary		!Unsuported
P5 					Portable graymap 		Binary
P6				 	Portable pixmap 		Binary*/
int pnm_set_imagetype(pnm_img* img, int p);

#ifdef __cplusplus
}
#endif

#endif //PPM_H
