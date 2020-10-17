#include <stdlib.h>
#include <gtk/gtk.h>

#include "../hdr/UI.h"

int main(int argc, char **argv)
{
    // GTK+ initialisation
    gtk_init(&argc, &argv);

    if (setup() == 1)
        return 1;

    // Main loop
    gtk_main();

    return EXIT_SUCCESS;
}
