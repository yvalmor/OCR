#include <stdlib.h>
#include <gtk/gtk.h>

#include "../hdr/UI.h"

#include "../hdr/bitmap.h"

void loadImage(char *path);

int main(__attribute((unused)) int argc, __attribute((unused))char **argv)
{
    if (Init_Sdl())
        return EXIT_FAILURE;
  
    // GTK+ initialisation
    gtk_init(&argc, &argv);

    if (setup() == 1)
        return EXIT_FAILURE;

    // Main loop
    gtk_main();

    return EXIT_SUCCESS;
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