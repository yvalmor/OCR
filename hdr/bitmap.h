#ifndef OCR_BITMAP_H
#define OCR_BITMAP_H

#include <SDL2/SDL.h>

#include "list.h"

typedef struct Tag_PIXEL
{
    Uint8 r;
    Uint8 g;
    Uint8 b;
} PIXEL;

typedef struct tagIMAGE
{
    int rows;
    int columns;
    PIXEL *pixels;
} IMAGE;

int Init_Sdl();
SDL_Surface* load_image_surface(char *path);

void loadImage(char *path, int autoRot, int rotationAngle);
void loadImage_with_training(char *path, int autoRot, int rotationAngle, FILE *fp);
void create_Image(SDL_Surface *surface, IMAGE image);

Uint8* pixel_ref(SDL_Surface *surf, unsigned x, unsigned y);
void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel);
Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);

void create_Matrix(SDL_Surface *surface, IMAGE image);

void saveImageAsBMP(ImagePart *image, char *filename);

#endif //OCR_BITMAP_H
