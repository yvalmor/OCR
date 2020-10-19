#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "../hdr/bitmap.h"

SDL_Surface *load(char *file_name)
{
    SDL_Surface *surface;

    surface = SDL_LoadBMP(file_name);
    
    if(surface == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s\n", file_name, SDL_GetError());
        return NULL;
    }
    surface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA8888, 0);

    return surface;
}

Uint32 get_Pixel(SDL_Surface *surface, int x, int y)
{
    Uint8 *p = surface->pixels + y * surface->pitch + x * 4;
    return *(Uint32*)p;

}

PIXEL *create_Matrix(SDL_Surface *surface, int row, int column)
{
    PIXEL pixels[row][column]; 
    SDL_LockSurface(surface);

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < column; j++)
        {
            Uint8 r, g, b;
            Uint8 *red = &r;
            Uint8 *green = &g; 
            Uint8 *blue = &b;
            Uint32 pixel = get_Pixel(surface, i, j);
            SDL_GetRGB(pixel, surface->format, red, green, blue);
            PIXEL pix = (PIXEL){r, g, b};
            pixels[i][j] = pix;
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
        return NULL;
    }

    SDL_Surface *surface = load(file_name);

    if(surface == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s\n", file_name, SDL_GetError());
        return NULL;
    }
    atexit(SDL_Quit);

    int row = surface->w;
    int column = surface->h;

    PIXEL *pixels = malloc(sizeof(PIXEL) * row * column);
    pixels = create_Matrix(surface, row, column);

    IMAGE image = {row, column, pixels};
    IMAGE *im = &image;

    SDL_FreeSurface(surface);
    SDL_Quit();

    return im;
}

int save_Text(char *file_name, char *text)
{
    FILE *file = fopen(file_name, "w+");

    if(file == NULL)
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
