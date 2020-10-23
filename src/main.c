#include <stdlib.h>
#include <gtk/gtk.h>

#include "../hdr/UI.h"
#include "../hdr/bitmap.h"

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