#include <stdlib.h>
#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    // Variables
    GtkWidget * MainWindow = NULL;

    // GTK+ initialisation
    gtk_init(&argc, &argv);

    // Main window creation
    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    // Main loop
    gtk_widget_show(MainWindow);
    gtk_main();

    return EXIT_SUCCESS;
}