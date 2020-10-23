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

Uint8* pixel_ref(SDL_Surface *surf, unsigned x, unsigned y)
{
    int bpp = surf->format->BytesPerPixel;
    return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}

Uint32 get_pixel(SDL_Surface *surface, unsigned x, unsigned y)
{
    Uint8 *p = pixel_ref(surface, x, y);

    switch (surface->format->BytesPerPixel)
    {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;
    }

    return 0;
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
            Uint32 pixel = get_pixel(surface, j, i);
            SDL_GetRGB(pixel, surface->format, &r, &g, &b);
            printf("%4d ", r);
            (image.pixels + i * row + j) -> r = r;
            (image.pixels + i * row + j) -> g = g;
            (image.pixels + i * row + j) -> b = b;
        }
        printf("\n");
    }
    printf("\n");

    SDL_UnlockSurface(surface);
}

void create_Image(SDL_Surface  *surface, IMAGE image)
{
    create_Matrix(surface, image);

    SDL_FreeSurface(surface);
}