#ifndef BITMAP_H
#define BITMAP_H
#include <SDL/SDL.h>

typedef struct Tag_PIXEL
{
    uint8 r;
    uint8 g;
    uint8 b;
}
PIXEL;

typedef struct tagIMAGE
{
    int rows;
    int columns;
    PIXEL *pixels;
}
IMAGE;

SDL_Surface *load(char *file_name);

Uint32 get_Pixel(SDL_Surface *surface, int x, int y);

PIXEL *create_Matrix(SDL_Surface *surface, int row, int column);

IMAGE *create_Image(char *file_name);

int save_Text(char *file_name, char *text);

#endif
