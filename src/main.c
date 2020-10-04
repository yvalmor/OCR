#include <stdio.h>
#include <gtk/gtk.h>

#include "../hdr/UI.h"

int main(int argc, char **argv)
{
    char *string = "truc";

    printf("%s", string);

    // GTK+ initialisation
    gtk_init(&argc, &argv);

    Setup();

    // Main loop
    gtk_main();

    return EXIT_SUCCESS;
}