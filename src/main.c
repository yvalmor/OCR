#include <stdio.h>

#include "../hdr/bitmap.h"

void loadImage(char *path);

int main(__attribute((unused)) int argc, __attribute((unused))char **argv)
{
    if (Init_Sdl())
        exit(1);

    return 0;
}

void loadImage(char *path)
{
    SDL_Surface *surface = load_image_surface(path);

    int rows = surface->h;
    int columns = surface->w;

    PIXEL pixels[rows][columns];

    IMAGE image = {rows, columns, *pixels};

    create_Image(surface, image);

    printf("size:%dx%d\n", rows, columns);

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
            printf("%4d ", (image.pixels + i * rows + j)->r);
        printf("\n");
    }
}