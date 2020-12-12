#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <unistd.h>

#include "../hdr/UI.h"
#include "../hdr/bitmap.h"
#include "../hdr/network.h"
#include "../hdr/json.h"
#include "../hdr/main.h"

Network *net;
int debugMode;

int main(int argc, char **argv)
{
    if (argc > 2)
        return EXIT_FAILURE;

    debugMode =
        argc == 2 &&
        (strcmp(argv[1], "-d") == 0 ||
         strcmp(argv[1], "--debug") == 0) ? 1 : 0;

    if (Init_Sdl())
        return EXIT_FAILURE;

    char *network_save = "network.json";

    net = malloc(sizeof(Network));
    if (access(network_save, F_OK) == 0)
        parse_network_from_file(network_save, net);
    else
        create_network(net, 4, 4, 1024, 62);

    // GTK+ initialisation
    gtk_init(&argc, &argv);

    if (setup() == 1)
        return EXIT_FAILURE;

    // Main loop
    gtk_main();

    write_network(net, network_save);

    return EXIT_SUCCESS;
}
