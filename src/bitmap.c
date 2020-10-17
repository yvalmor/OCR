#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include "bitmap.h"

SDL_Surface *load(char *file_name)
{
    SDL_Surface *surface;

    surface = SDL_LoadBMP(file_name);
    
    if(surface == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s\n", file_name, SDL_GetError());
        return NULL;
    }

    return *surface;
}

Uint32 get_Pixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp)
    {
        case 1:
             return p;

        case 2:
             {
                 Uint16 *result = p;
                 return result;
             }

        case 3:
             {
                 if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                     return p[0] << 16 | p[1] << 8 | p[2];
                 else
                     return p[0] | p[1] << 8 | p[2] << 16;
             }

        case 4:
             {
                 Uint32 *result = p;
                 return result;
             }

        default:
             return 0;
    }
}

PIXEL *create_Matrix(SDL_Surface *surface, int row, int column)
{
    PIXEL pixels[row][columns];
    PIXEL pix = malloc(sizeof(PIXEL));
    SDL_LockSurface(surface);


    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < column; j++)
        {
            Uint8 r, g, b;
            Uint32 pixel = get_Pixel(surface, i, j)
            SDL_GetRGB(pixel, surface->format, *r, *g, *b)
            pixels[i][j] = {r, g, b}
        }
    }

    SDL_UnlockSurface(surface);
    return *pixels;
}

IMAGE *create_Image(char *file_name)
{
    if((SDL_Init(SDL_INIT_VIDEO) == -1))
    {
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        exit(NULL);
    }

    SDL_Surface *surface = load(*file_name);

    if(surface == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s\n", file_name, SDL_GetError());
        return NULL;
    }
    int row = surface->w;
    int columns = surface->h;

    PIXEL *pixels = create_Matrix(surface, row, column);

    IMAGE image = {row, column, *pixels};

    return *image;
}

int save_Text(char *file_name, char *text)
{
    FILE *file = fopen(file_name, "w+")

    if(fichier == NULL)
    {
        printf("Impossible to open the file \"%s\"", file_name);
        return 1;
    }
    else
    {
        fprintf(file, text);
        fclose(file);
    }

    return 0;
}
