#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

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

    if (argc == 2)
        if (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--debug") == 0)
            debugMode = 1;
        else
        {
            printf("incorrect flags, valid options are '-d' or '--debug'\n");
            exit(1);
        }
    else
        debugMode = 0;

    if (debugMode)
    {
        struct stat st = {0};

        if (stat("letters/", &st) == -1)
            mkdir("letters/", 0700);
        if (stat("lines/", &st) == -1)
            mkdir("lines/", 0700);
    }

    if (Init_Sdl())
        return EXIT_FAILURE;

    char *network_save = "../network.json";

    net = malloc(sizeof(Network));
    if (access(network_save, F_OK) == 0)
        parse_network_from_file(network_save, net);
    else
        create_network(net, 4, 64, 32*32, 62);

    // GTK+ initialisation
    gtk_init(&argc, &argv);

    if (setup() == 1)
        return EXIT_FAILURE;

    // Main loop
    gtk_main();

    write_network(net, network_save);

    return EXIT_SUCCESS;
}
