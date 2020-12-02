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
void loadImage(char *path);
void create_Image(SDL_Surface *surface, IMAGE image);
Uint8* pixel_ref(SDL_Surface *surf, unsigned x, unsigned y);
Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y);
void create_Matrix(SDL_Surface *surface, IMAGE image);

#endif //OCR_BITMAP_H
