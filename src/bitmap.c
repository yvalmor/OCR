#include <SDL2/SDL.h>

#include "../hdr/bitmap.h"

int Init_Sdl()
{
    if((SDL_Init(SDL_INIT_VIDEO) == -1))
    {
        printf("Could not initialize SDL: %s.\n", SDL_GetError());
        return 1;
    }

    atexit(SDL_Quit);

    return 0;
}

SDL_Surface* load_image_surface(char *path)
{
    SDL_Surface *img;

    img = SDL_LoadBMP(path);

    if(img == NULL)
    {
        fprintf(stderr, "Couldn't load %s: %s\n", path, SDL_GetError());
        exit(1);
    }

    return img;
}

IMAGE load_image(SDL_Surface *surface)
{
    int w = surface->w;
    int h = surface->h;

    PIXEL pixels[h][w];

    IMAGE image = {};

    return image;
}

Uint32 get_Pixel(SDL_Surface *surface, int x, int y)
{
    Uint8 *p = surface->pixels + y * surface->pitch + x * 4;
    return *(Uint32*)p;
}

void create_Matrix(SDL_Surface *surface, IMAGE image)
{
    int row = image.rows;
    int columns = image.columns;

    SDL_LockSurface(surface);

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            Uint8 r = 0, g = 0, b = 0;
            Uint32 pixel = get_Pixel(surface, j, i);
            SDL_GetRGB(pixel, surface->format, &r, &g, &b);
            (image.pixels + i * row + j) -> r = r;
            (image.pixels + i * row + j) -> g = g;
            (image.pixels + i * row + j) -> b = b;
        }
    }

    SDL_UnlockSurface(surface);
}

void create_Image(SDL_Surface  *surface, IMAGE image)
{
    create_Matrix(surface, image);

    SDL_FreeSurface(surface);
}