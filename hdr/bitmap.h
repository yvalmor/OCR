#ifndef OCR_BITMAP_H
#define OCR_BITMAP_H

#include <SDL2/SDL.h>

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
IMAGE load_image(SDL_Surface *surface);
Uint32 get_Pixel(SDL_Surface *surface, int x, int y);
void create_Image(SDL_Surface *surface, IMAGE image);
void create_Matrix(SDL_Surface *surface, IMAGE image);

#endif //OCR_BITMAP_H
