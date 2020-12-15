#include <string.h>
#include <SDL2/SDL.h>
#include <stdio.h>

#include "../hdr/bitmap.h"
#include "../hdr/UI.h"
#include "../hdr/text.h"
#include "../hdr/processing.h"
#include "../hdr/segmentation.h"
#include "../hdr/rlsa.h"
#include "../hdr/list.h"
#include "../hdr/main.h"
#include "../hdr/rotation.h"

extern int debugMode;


void saveRGBImageAsBMP(IMAGE *image, char *filename);


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

void put_pixel(SDL_Surface *surface, unsigned x, unsigned y, Uint32 pixel)
{
    Uint8 *p = pixel_ref(surface, x, y);

    switch(surface->format->BytesPerPixel)
    {
        case 1:
            *p = pixel;
            break;

        case 2:
            *(Uint16 *)p = pixel;
            break;

        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            }
            else
            {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;

        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}


void loadImage(char *path, int autoRot, int rotationAngle)
{
    SDL_Surface *surface = load_image_surface(path);

    if (autoRot)
    {
        double angle = find_angle(surface);
        surface = SDL_RotateImage(surface, -angle);
    }
    else
        surface = SDL_RotateImage(surface, -rotationAngle);

    int rows = surface->h;
    int columns = surface->w;

    PIXEL pixels[rows][columns];

    IMAGE image = {rows, columns, *pixels};
    create_Image(surface, image);

    if (debugMode)
        saveRGBImageAsBMP(&image, "rotated_image.bmp");

    int *intensity = calloc(rows * columns, sizeof(int));

    toGrayscale(image, intensity);

    toBlackAndWhite2(image, intensity);

    char *result = build_text(intensity, rows, columns);

    set_text(result);

    free(result);
}


void loadImage_with_training(char *path, int autoRot,
                             int rotationAngle, FILE *fp)
{
    SDL_Surface *surface = load_image_surface(path);

    if (autoRot)
    {
        double angle = find_angle(surface);
        surface = SDL_RotateImage(surface, -angle);
    }
    else
        surface = SDL_RotateImage(surface, -rotationAngle);

    int rows = surface->h;
    int columns = surface->w;

    PIXEL pixels[rows][columns];

    IMAGE image = {rows, columns, *pixels};
    create_Image(surface, image);

    if (debugMode)
        saveRGBImageAsBMP(&image, "rotated_image.bmp");

    int intensity[rows][columns];

    toGrayscale(image, *intensity);

    toBlackAndWhite2(image, *intensity);

    build_text_with_training(*intensity, rows, columns, fp);
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
            (image.pixels + i * columns + j) -> r = r;
            (image.pixels + i * columns + j) -> g = g;
            (image.pixels + i * columns + j) -> b = b;
        }
    }

    SDL_UnlockSurface(surface);
}


void create_Image(SDL_Surface  *surface, IMAGE image)
{
    create_Matrix(surface, image);

    SDL_FreeSurface(surface);
}


void saveImageAsBMP(ImagePart *image, char *filename)
{
    SDL_Surface *surface;
    surface = SDL_CreateRGBSurface(0, image->cols, image->rows,
                                   32, 0, 0, 0, 0);

    unsigned int cols = image->cols,
                 rows = image->rows;

    for (unsigned int x = 0; x < cols; x++)
        for (unsigned int y = 0; y < rows; y++)
            {
                int val = image->img[y * image->cols + x];
                Uint32 value = SDL_MapRGB(surface->format, val*255,
                                          val*255, val*255);
                put_pixel(surface, x, y, value);
            }

    SDL_SaveBMP(surface, filename);
    SDL_FreeSurface(surface);
}


void saveRGBImageAsBMP(IMAGE *image, char *filename)
{
    unsigned int cols = image->columns,
                 rows = image->rows;

    SDL_Surface *surface;
    surface = SDL_CreateRGBSurface(0, cols, rows,
                                   32, 0, 0, 0, 0);

    for (unsigned int x = 0; x < cols; x++)
        for (unsigned int y = 0; y < rows; y++)
            {
                Uint8 r = image->pixels[y * cols + x].r,
                      g = image->pixels[y * cols + x].g,
                      b = image->pixels[y * cols + x].b;

                Uint32 value = SDL_MapRGB(surface->format, r, g, b);
                put_pixel(surface, x, y, value);
            }

    SDL_SaveBMP(surface, filename);
    SDL_FreeSurface(surface);
}

