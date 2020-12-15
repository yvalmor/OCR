#ifndef OCR_BITMAP_H
#define OCR_BITMAP_H

#include <SDL2/SDL.h>

#include "list.h"


/**
 * The structure that contains the colors of a pixel
 */
typedef struct Tag_PIXEL
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
} PIXEL;


/**
 * The structure that contains a non-binarized image
 */
typedef struct tagIMAGE
{
    int rows;
    int columns;
    PIXEL *pixels;
} IMAGE;


/**
 * Initializes the SDL library
 *
 * @author Souleymane Sentici
 * @returns 1 if there is an error, 0 otherwise
 */
int Init_Sdl();


/**
 * Loads a bitmap file into an SDL_Surface structure
 *
 * @author Souleymane Sentici
 * @returns a pointer to an SDL_Surface
 * @param path the path to the bitmap file
 */
SDL_Surface* load_image_surface(char *path);


/**
 * Loads a bitmap file, creates an IMAGE structure from it, preprocess it and
 * saves its processed pixel data in a file
 *
 * @author Souleymane Sentici
 * @param path the path of the bitmap file to load
 * @see toBlackAndWhite that makes all pixels in the loaded image into either
 *      black or white pixels != to_matrix_bw
 * @see to_matrix_bw that saves a black and white matrix's pixel data in a
 *      string
 */
void loadImage(char *path, int autoRot, int rotationAngle);


/**
 * Loads a bitmap file, creates an IMAGE structure from it, preprocess it and
 * saves its processed pixel data in a file
 *
 * @author Yvon Morice
 * @param path the path of the bitmap file to load
 * @see toBlackAndWhite that makes all pixels in the loaded image into either
 *      black or white pixels != to_matrix_bw
 * @see to_matrix_bw that saves a black and white matrix's pixel data in a
 *      string
 */
void loadImage_with_training(char *path, int autoRot, int rotationAngle, FILE *fp);


/**
 * Fills a given IMAGE with the info of a bitmap loaded in a surface
 *
 * @author Souleymane Sentici
 * @param surface, the surface in which the bitmap is loaded
 * @param image, the IMAGE that will contain the bitmap info
 * @see create_Matrix
 */
void create_Image(SDL_Surface *surface, IMAGE image);


/**
 * Gets the pixel in the (x, y) position of a given SDL_Surface while taking
 * in account its bpp (Bytes per pixel) format
 *
 * @author Souleymane Sentici
 * @returns a Uint8 pixel from a given image
 * @param surf the surface containing the image to take a pixel from
 * @param x the x-axis coordinate of the pixel to return
 * @param y the y-axis coordinate of the pixel to return
 */
Uint8* pixel_ref(SDL_Surface *surf, unsigned x, unsigned y);


/**
 * Changes a given pixel in an SDL_Surface
 *
 * @author Yvon Morice
 * @param surface, the SDL_Surface which we want to change
 * @param x, the x coordinates of the pixel
 * @param y, the y coordinates of the pixel
 * @param pixel, the new color of the pixel
 */
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);


/**
 * Gets the pixel in the (x, y) position of a given SDL_Surface while taking
 * in account its bpp (Bytes per pixel) format
 *
 * @author Souleymane Sentici
 * @returns a Uint32 pixel from a given image
 * @param surf the surface containing the image to take a pixel from
 * @param x the x-axis coordinate of the pixel to return
 * @param y the y-axis coordinate of the pixel to return
 * @see pixel_ref
 */
Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);


/**
 * Creates a matrix containing the pixel data of an bitmap loaded in an
 * SDL_Surface and puts it in an IMAGE
 *
 * @author Souleymane Sentici
 * @param surface the surface in which the bitmap is loaded
 * @param image the IMAGE in which the pixel data matrix will be stored
 * @see get_pixel
 */
void create_Matrix(SDL_Surface *surface, IMAGE image);


/**
 * Saves the content of a part of an image in a file
 *
 * @author Yvon Morice
 * @param image, the part of the image that we wish to save
 * @param filename, the name of the file
 */
void saveImageAsBMP(ImagePart *image, char *filename);


/**
 * Saves the content of a part of an image that hasn't been
 * binarized yet in a file
 *
 * @author Yvon Morice
 * @param image, the part of the image that we wish to save
 * @param filename, the name of the file
 */
void saveRGBImageAsBMP(IMAGE *image, char *filename);

#endif
