#include <stdlib.h>
#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    // Variables
    GtkWidget *MainWindow = NULL;

    // GTK+ initialisation
    gtk_init(&argc, &argv);

    // Main window creation
    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    // Main window settings
    gtk_window_set_title(GTK_WINDOW(MainWindow), "OCR");
    gtk_window_set_default_size(GTK_WINDOW(MainWindow), 1280, 720);
    gtk_window_set_position(GTK_WINDOW(MainWindow), GTK_WIN_POS_CENTER);

    // Main loop + showing main window
    gtk_widget_show_all();
    gtk_main();

    return EXIT_SUCCESS;
}